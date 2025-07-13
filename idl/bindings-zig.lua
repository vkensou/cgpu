local codegen = require "codegen"
local idl = codegen.idl "cgpu2.idl"

local zig_template = [[
// Copyright 2011-2023 Branimir Karadzic. All rights reserved.
// License: https://github.com/bkaradzic/bgfx/blob/master/LICENSE

//
// AUTO GENERATED! DO NOT EDIT!
//

const std = @import("std");

pub const HWND = *anyopaque;
pub const ANativeWindowPtr = *anyopaque;

pub const Error = error{
    CreateFailed,
};

$types
$funcs]]

local function upperCamelcase_to_underscorecase(name)
	local tmp = {}
	for v in name:gmatch "[%u%d]+[%l%d]*" do
		tmp[#tmp+1] = v:lower()
	end
	return table.concat(tmp, "_")
end

local function lowerCamelcase_to_underscorecase(name)
	local tmp = {}
	for v in name:gmatch "[%u%l%d][%l%d]*" do
		tmp[#tmp+1] = v:lower()
	end
	return table.concat(tmp, "_")
end

local function Set(list)
    local set = {}
    for _, l in ipairs(list) do
        set[l] = true
    end
    return set
end

local keywords = Set {"error", "opaque", "export"}

local function handle_embed_keyword(name)
    if keywords[name] or name:match("^%d") then
        return '@"' .. name .. '"'
    else
        return name
    end
end

local function namealign(name, align)
    align = align or DEFAULT_NAME_ALIGN
    return string.rep(" ", align - #name)
end

function trimRight(s)
    return s:gsub("%s*$", "")
end

local function isempty(s)
	return s == nil or s == ''
end

local function hasPrefix(str, prefix)
	return prefix == "" or str:sub(1, #prefix) == prefix
end

local function hasSuffix(str, suffix)
	return suffix == "" or str:sub(- #suffix) == suffix
end

local function isMatch(str, sub)
	return str:match(sub) == sub
end

local function isFuncPtr(str)
	return idl.types[str] ~= nil and idl.types[str].args
end

local function isId(str)
	return idl.types[str] ~= nil and idl.types[str].id
end

local enum = {}
local funcptr = {}

local function convert_array(member)
	if string.find(member.array, "::") then
		return enum[member.array]
	else
		return member.array:match "%[(.*)%]"
	end
end

local function gisub(s, pat, repl, n)
	pat = string.gsub(pat, '(%a)', function(v)
		return '[' .. string.upper(v) .. string.lower(v) .. ']'
	end)
	if n then
		return string.gsub(s, pat, repl, n)
	else
		return string.gsub(s, pat, repl)
	end
end

local function convert_type_02(arg)
	if isMatch(arg.ctype, "uint64_t") then
		return arg.ctype:gsub("uint64_t", "u64")
	elseif isMatch(arg.ctype, "int64_t") then
		return arg.ctype:gsub("int64_t", "i64")
	elseif isMatch(arg.ctype, "uint32_t") then
		return arg.ctype:gsub("uint32_t", "u32")
	elseif isMatch(arg.ctype, "int32_t") then
		return arg.ctype:gsub("int32_t", "i32")
	elseif isMatch(arg.ctype, "uint16_t") then
		return arg.ctype:gsub("uint16_t", "u16")
	elseif isMatch(arg.ctype, "uint8_t") then
		return arg.ctype:gsub("uint8_t", "u8")
	elseif isMatch(arg.ctype, "uintptr_t") then
		return arg.ctype:gsub("uintptr_t", "usize")
	elseif isMatch(arg.ctype, "float") then
		return arg.ctype:gsub("float", "f32")
	elseif isMatch(arg.ctype, "double") then
		return arg.ctype:gsub("double", "f64")
	elseif arg.ctype == "const char*" then
		return "[*c]const u8"
	elseif isMatch(arg.ctype, "char") then
		return arg.ctype:gsub("char", "u8")
	elseif isMatch(arg.ctype, "size_t") then
		return arg.ctype:gsub("size_t", "usize")
	elseif hasSuffix(arg.fulltype, "Handle") then
		return arg.fulltype
	elseif hasSuffix(arg.fulltype, "Id") then
		return arg.fulltype
	elseif arg.ctype == "..." then
		return "..."
	elseif arg.ctype == "va_list" or arg.fulltype == "bx::AllocatorI*" or arg.fulltype == "CallbackI*" or arg.fulltype ==
		"ReleaseFn" then
		return "?*anyopaque"
	end

	return arg.fulltype
end

local function convert_type_0(arg)
	if arg == "cstring" then
		return "[*:0]const u8"
	elseif arg == "uint64_t" then
		return "u64"
	elseif arg == "int64_t" then
		return "i64"
	elseif arg == "uint32_t" then
		return "u32"
	elseif arg == "int32_t" then
		return "i32"
	elseif arg == "uint16_t" then
		return "u16"
	elseif arg == "int16_t" then
		return "i16"
	elseif arg == "uint8_t" then
		return "u8"
	elseif arg == "int8_t" then
		return "i8"
	elseif arg == "float" then
		return "f32"
	elseif arg == "double" then
		return "f64"
	elseif arg == "size_t" then
		return "usize"
	elseif arg == "char" then
		return "u8"
	elseif funcptr[arg] ~= nil then
		return "?*const " .. arg, "null"
	else
		arg = arg:gsub("::Enum", "")
		return arg
	end
end

local function convert_type(arg)
	if arg.optional then
		return "?" .. convert_type(arg.fulltype), "null"
	elseif arg.ptr then
		return "*" .. convert_type(arg.fulltype)
	elseif arg.array then
		if arg.array_at then
			if arg.array_at.number then
				return "[" .. tostring(arg.array_at.number) .. "]" .. convert_type(arg.fulltype)		
			elseif arg.array_at.enum then
				local array_count = convert_array(arg)
				return "[" .. tostring(array_count) .. "]" .. convert_type(arg.fulltype)		
			elseif arg.array_at.const_value then
				return "[" .. arg.array_at.const_value .. "]" .. convert_type(arg.fulltype)
			elseif arg.array_at.indefinite then
				return "[*]" .. convert_type(arg.fulltype)
			end
		end
		error("no array_at")
	elseif arg.const then
		return "const " .. convert_type(arg.fulltype)
	else
		local fulltype
		if type(arg.fulltype) == "string" then
			fulltype = arg.fulltype 
		elseif type(arg) == "string" then
			fulltype = arg
		end
		if type(fulltype) == "string" then
			return convert_type_0(fulltype)
		end

		error("catch")
	end
end

local function convert_type2(arg, not_optional)
	local ctype = convert_type_0(arg)

	if ctype == "void*" then
		return "?*anyopaque", "null"
	elseif ctype == "void**" then
		return "[*c]?*anyopaque", "null"
	elseif isFuncPtr(arg.fulltype) then
		return "?*const " .. arg.fulltype, "null"
	elseif isId(arg.fulltype) and arg.array == nil then
		return not_optional and arg.fulltype or "?" .. arg.fulltype
	end 
	
	ctype = ctype:gsub("::Enum", "")
	ctype = ctype:gsub(" &", "*")
	ctype = ctype:gsub("&", "*")
	ctype = ctype:gsub("char", "u8")
	ctype = ctype:gsub("float", "f32")
	ctype = ctype:gsub("const void%*", "?*const anyopaque")
	ctype = ctype:gsub("Encoder%*", "?*Encoder")

	if hasSuffix(ctype, "void*") then
		ctype = ctype:gsub("void%*", "?*anyopaque");
	elseif hasSuffix(ctype, "*") then
		ctype = "[*c]" .. ctype:gsub("*", "")
	end

	if arg.array ~= nil then
		-- ctype = ctype:gsub("const ", "")
		ctype = convert_array(arg) .. ctype
	end

	if arg.optional then
		return "?" .. ctype, "null"
	else
		return ctype
	end
end

local function convert_struct_type(arg)
	return convert_type(arg)
end

local function convert_ret_type(arg)
	return convert_type(arg)
end

local function wrap_simple_func(func, args, argNames)
	local zigFunc = {}
	local zigFuncTemplate = [[pub inline fn $func($params) $ret {
    return $cfunc($args);
}]]

	local zigCreateFuncTemplate = [[pub inline fn $func($params) Error!$ret {
    const result = $cfunc($args);
    return if (result) |result_object|
        result_object
    else
        Error.CreateFailed;
}]]

	-- transform name to camelCase from snake_case
	zigFunc.func = func.cname:gsub("_(.)", func.cname.upper)
	-- make 2d/3d upper case 2D/3D
	zigFunc.func = zigFunc.func:gsub("%dd", zigFunc.func.upper);
	zigFunc.params = table.concat(args, ", ")
	zigFunc.ret = convert_ret_type(func.ret)
	local createFunc = zigFunc.ret:match("^?(.*)") ~= nil
	if createFunc then
		zigFunc.ret = zigFunc.ret:gsub("^?", "")
	end
	zigFunc.cfunc = "cgpu_" .. func.cname
	zigFunc.args = table.concat(argNames, ", ")
	if createFunc then
		return zigCreateFuncTemplate:gsub("$(%l+)", zigFunc)
	else
		return zigFuncTemplate:gsub("$(%l+)", zigFunc)
	end
end

local function wrap_method(func, type, args, argNames, indent)
	local zigFunc = {}
	local zigFuncTemplate = [[%spub inline fn $func($params) $ret {
    %sreturn $cfunc($args);
%s}]]

	local zigCreateFuncTemplate = [[%spub inline fn $func($params) Error!$ret {
    %sconst result = $cfunc($args);
    %sreturn if (result) |result_object|
        %sresult_object
    %selse
        %sError.CreateFailed;
%s}]]

	zigFuncTemplate = string.format(zigFuncTemplate, indent, indent, indent);
	zigCreateFuncTemplate = string.format(zigCreateFuncTemplate, indent, indent, indent, indent, indent, indent, indent);

	-- transform name to camelCase from snake_case
	zigFunc.func = func.cname:gsub("_(.)", func.cname.upper)
	-- remove type from name
	zigFunc.func = gisub(zigFunc.func, type, "");
	-- make first letter lowercase
	zigFunc.func = zigFunc.func:gsub("^%L", string.lower)
	-- make 2d/3d upper case 2D/3D
	zigFunc.func = zigFunc.func:gsub("%dd", zigFunc.func.upper);
	zigFunc.params = table.concat(args, ", ")
	zigFunc.ret = convert_ret_type(func.ret)
	-- remove C API pointer [*c] for fluent interfaces
	if zigFunc.ret == ("[*c]" .. type) then
		zigFunc.ret = zigFunc.ret:gsub("%[%*c%]", "*")
	end
	local createFunc = zigFunc.ret:match("^?(.*)") ~= nil
	if createFunc then
		zigFunc.ret = zigFunc.ret:gsub("^?", "")
	end
	zigFunc.cfunc = "cgpu_" .. func.cname
	zigFunc.args = table.concat(argNames, ", ")
	if createFunc then
		return zigCreateFuncTemplate:gsub("$(%l+)", zigFunc)
	else
		return zigFuncTemplate:gsub("$(%l+)", zigFunc)
	end
end

local converter = {}
local yield = coroutine.yield
local gen = {}

function gen.gen()
	-- find the functions that have `this` first argument
	-- these belong to a type (struct) and we need to add them when converting structures
	local methods = {}
	for _, func in ipairs(idl["funcs"]) do
		if func.this ~= nil then
			if methods[func.this_type.type] == nil then
				methods[func.this_type.type] = {}
			end
			table.insert(methods[func.this_type.type], func)
		end
	end

	local r = zig_template:gsub("$(%l+)", function(what)
		local tmp = {}
		for _, object in ipairs(idl[what]) do
			local co = coroutine.create(converter[what])
			local any
			-- we're pretty confident there are no types that have the same name with a func
			local funcs = methods[object.name]
			while true do
				local ok, v = coroutine.resume(co, {
					obj = object,
					funcs = funcs
				})
				assert(ok, debug.traceback(co, v))
				if not v then
					break
				end
				table.insert(tmp, v)
				any = true
			end
			if any and tmp[#tmp] ~= "" then
				table.insert(tmp, "")
			end
		end
		return table.concat(tmp, "\n")
	end)
	return r
end

local function flat_combined(flag, item, added)
    for i = 1, #flag.flag do
        if flag.flag[i].name == item then
            if #flag.flag[i] == 0 then
                added[item] = true
            else
                for k, v in ipairs(flag.flag[i]) do
                    flat_combined(flag, v, added)
                end
            end
            break
        end
    end
end


local function FlagBlock(typ)
	local format = "0x%08x"
	local enumType = "u32"
	if typ.bits == 64 then
		format = "0x%016x"
		enumType = "u64"
	elseif typ.bits == 16 then
		format = "0x%04x"
		enumType = "u16"
	end

	local name = typ.name
	yield("pub const " .. name .. " = packed struct(" .. enumType .. ") {")

    local used = 0
	for idx, flag in ipairs(typ.flag) do
        local value = flag.value
        if value ~= 0 and #flag == 0 then
            if flag.comment ~= nil then
                if idx ~= 1 then
                    yield("")
                end

                for _, comment in ipairs(flag.comment) do
                    yield("/// " .. comment)
                end
            end

            local comment = ""

            local zname = handle_embed_keyword(upperCamelcase_to_underscorecase(flag.name))
            local code = string.format("    %s: bool = false, // (%2d) %s%s", zname, used, namealign(comment, 30), comment)
			code = trimRight(code)
            yield(code)
            used = used + 1
        end
	end

    if used < typ.bits then
        yield(string.format("    padding: u%d = 0,", typ.bits - used))
    end

    local flat_flags = {}
    for index, item in ipairs(typ.flag) do
        if #item > 0 then
            local added = {}
            for k, v in ipairs(item) do
                flat_combined(typ, v, added)
            end

            flat_flags[index] = {}
            local i = 1
            for k, _ in pairs(added) do
                flat_flags[index][i] = k
                i = i + 1
            end
        end
    end


	for idx, flag in ipairs(typ.flag) do
        if #flag > 0 then
            local sets = {}
            local flat_flag = flat_flags[idx]
			table.sort(flat_flag)
            for _, v in ipairs(flat_flag) do
                local zv = upperCamelcase_to_underscorecase(v)
                sets[#sets + 1] = "." .. zv .. " = true"
            end
            local zname = handle_embed_keyword(upperCamelcase_to_underscorecase(flag.name))
            yield(string.format("    pub const %s: %s = .{ %s };", zname, name, table.concat(sets, ", ")))
        end
    end

    yield("};")
end

local function convert_member_name(name)
	if name == "type" then 
		return "_type"
	end
	return lowerCamelcase_to_underscorecase(name)
end

local function convert_struct_member(member, union)
	local name = convert_member_name(member.name)
	local type, default = convert_struct_type(member)
	local q = name .. ": " .. type
	if default == nil or union then
		return q
	else
		return q .. " = " .. default
	end
end

local namespace = ""

function converter.types(params)
	local typ = params.obj
	local funcs = params.funcs
	if typ.handle then
		yield("pub const " .. typ.name .. " = extern struct {")
		yield("    idx: c_ushort,")
		yield("};")
	elseif typ.id then
		local t = typ.name:match "([%u%l%d]*)Id"
		yield("pub const " .. typ.name .. " = *" .. t .. ";")
	elseif hasSuffix(typ.name, "::Enum") then
		yield("pub const " .. typ.typename .. " = enum(u32) {")
		for idx, enum in ipairs(typ.enum) do
            local comment = ""
            if enum.comment then
                comment = table.concat(enum.comment, " ")
            end
            local iname = handle_embed_keyword(upperCamelcase_to_underscorecase(enum.name))
			local code = string.format("    %s, // (%2d) %s%s", iname, idx - 1, namealign(comment, 30), comment)
			code = trimRight(code)
            yield(code)
		end
		yield("};")

		enum["[" .. typ.typename .. "::Count]"] = #typ.enum

	elseif typ.bits ~= nil then
		FlagBlock(typ)
	elseif typ.struct ~= nil then
		local skip = false

        local indent = 0
		if typ.namespace ~= nil then
			if namespace ~= typ.namespace then
				yield("pub const " .. typ.namespace .. " = extern struct {")
				namespace = typ.namespace
				indent = indent + 1
			end
		elseif namespace ~= "" then
			indent = indent + 1
			namespace = ""
			skip = true
		end

		if #typ.struct > 0 then
			if not skip then
				if typ.union then
					yield(string.rep("    ", indent) .. "pub const " .. typ.name .. " = extern union {")
				else	
					yield(string.rep("    ", indent) .. "pub const " .. typ.name .. " = extern struct {")
				end
			end

			for _, member in ipairs(typ.struct) do
				yield(string.rep("    ", indent + 1) .. convert_struct_member(member, typ.union) .. ",")
			end
			if funcs ~= nil then
				for _, func in ipairs(funcs) do
					converter.funcs({
						obj = func,
						asMethod = true
					})
				end
			end

			yield(string.rep("    ", indent) .. "};")
		else
			if typ.union then
				yield(string.rep("    ", indent) .. "pub const " .. typ.name .. " = extern union {};")
			else	
				yield(string.rep("    ", indent) .. "pub const " .. typ.name .. " = extern struct {};")
			end
		end
	elseif typ.args then
		local args = {}
		local argNames = {}
		local func_indent = ""

		for _, arg in ipairs(typ.args) do
			local argName = arg.name
			-- local argName = arg.name:gsub("_", "")
			-- argName = argName:gsub("enum", "enumeration")
			-- argName = argName:gsub("type_", '@"type"')
			if not isempty(argName) then
				table.insert(argNames, argName)
				table.insert(args, convert_member_name(argName) .. ": " .. convert_type(arg, true))
			else
				local q = convert_type(arg, true)
				table.insert(args, q)
			end
		end

		if (params.asMethod == true) then
			yield(wrap_method(func, typ.this_type.type, args, argNames, func_indent))
		else
			yield(
				"pub const " .. typ.name .. " = fn (" .. table.concat(args, ", ") .. ") callconv(.C) " .. convert_ret_type(typ.ret) ..
				";")
		end

		funcptr[typ.name] = typ
	elseif typ.const_value then
		yield("pub const " .. typ.name .. ": u32 = " .. tostring(typ.value) .. ";")
	end
end

function converter.funcs(params)
	local func = params.obj
	if func.cpponly then
		return
	elseif func.cppinline and not func.conly then
		return
	end

	-- skip for now, don't know how to handle variadic functions
	if func.cname == "dbg_text_printf" or func.cname == "dbg_text_vprintf" then
		return
	end

    local indent = "    "
	local func_indent = (params.asMethod == true and indent or "")

	if func.comments ~= nil then
		for _, line in ipairs(func.comments) do
			yield(func_indent .. "/// " .. line)
		end

		local hasParams = false

		for _, arg in ipairs(func.args) do
			if arg.comment ~= nil then
				local comment = table.concat(arg.comment, " ")

				yield(func_indent .. "/// <param name=\"" .. arg.name .. "\">" .. comment .. "</param>")

				hasParams = true
			end
		end
	end

	local args = {}
	local argNames = {}

	if func.this ~= nil then
		local ptr = "[*c]"
		if params.asMethod == true then
			ptr = "*"
		end
		-- print("Function " .. func.name .. " has this: " .. func.this_type.type)
		if func.const ~= nil then
			ptr = ptr .. "const "
		end

		if func.this_type.type == "Encoder" then
			ptr = "?*"
		end
		args[1] = "self: " .. ptr .. func.this_type.type
		argNames[1] = "self"
	end
	for _, arg in ipairs(func.args) do
		local argName = convert_member_name(arg.name)
		-- local argName = arg.name:gsub("_", "")
		-- argName = argName:gsub("enum", "enumeration")
		-- argName = argName:gsub("type_", '@"type"')
		if not isempty(argName) then
			table.insert(argNames, argName)
			table.insert(args, argName .. ": " .. convert_type(arg, true))
		else
			table.insert(args, convert_type(arg, true))
		end
	end

	if (params.asMethod == true) then
		yield(wrap_method(func, func.this_type.type, args, argNames, func_indent))
	else
		if func.this == nil then
			yield(wrap_simple_func(func, args, argNames))
		end
		yield(
			"extern fn cgpu_" .. func.cname .. "(" .. table.concat(args, ", ") .. ") " .. convert_ret_type(func.ret) ..
			";")
	end
end

function gen.write(codes, outputfile)
	local out = assert(io.open(outputfile, "wb"))
	out:write(codes)
	out:close()
	print("Generating: " .. outputfile)
end

if (...) == nil then
	-- run `lua bindings-zig.lua` in command line
	print(gen.gen())
end

return gen
