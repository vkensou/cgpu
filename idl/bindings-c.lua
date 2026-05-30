local codegen = require "codegen"

local func_actions = {

	c99              = "\n",
	c99decl          = "\n",
	cppdecl          = "\n",
	interface_struct = "\n\t",
	interface_import = ",\n\t\t\t",
	c99_interface    = "\n",
	cpp_interface    = "\n",
	c99_functionid   = "\n\t",
	cpp_functionid   = "\n\t\t",
}

local type_actions = {

	consts    = "\n",
	cconsts    = "\n",
	cflags    = "\n",
	enums     = "\n",
	cenums    = "\n",
	structs   = "\n",
	cstructs  = "\n",
	handles   = "\n",
	chandles  = "\n",
	ids       = "\n",
	cids       = "\n",
	funcptrs  = "\n",
	cfuncptrs = "\n",
	cswitches  = "\n",
}

local function cfunc(f)
	return function(func)
		if (not func.cpponly) or func.conly then
			return f(func)
		end
	end
end

local funcgen = {}

local functemp = {}

functemp.interface_struct = "$CRET (*$CFUNCNAME)($CARGS);"
functemp.interface_import = "bgfx_$CFUNCNAME"
functemp.c99_interface = [[
BGFX_C_API $CRET bgfx_$CFUNCNAME($CARGS)
{
	$CONVERSIONCTOC
	$PRERETCTOCg_interface->$CFUNCNAME($CALLARGS);
	$POSTRETCTOC
}
]]
functemp.c99_functionid = "BGFX_FUNCTION_ID_$CFUNCNAMEUPPER,"
functemp.cpp_functionid = "$CFUNCNAMECAML,"

for action,temp in pairs(functemp) do
	funcgen[action] = cfunc(function(func)
		return codegen.apply_functemp(func, temp)
	end)
end

funcgen.cpp_interface= cfunc(function(func)
	if not func.cfunc and not func.conly then
		return codegen.apply_functemp(func, [[
$RET $CLASSNAME$FUNCNAME($CPPARGS)$CONST
{
	$CONVERSIONCTOCPP
	$PRERETCPPTOCg_interface->$CFUNCNAME($CALLARGSCPPTOC);
	$POSTRETCPPTOC
}
]])
	end
end)

funcgen.c99 = cfunc(function(func)
	local temp
	if func.cfunc then
		temp = "/* BGFX_C_API $CRET bgfx_$CFUNCNAME($CARGS) */\n"
	else
		temp = [[
BGFX_C_API $CRET bgfx_$CFUNCNAME($CARGS)
{
	$CONVERSION
	$PRERET$CPPFUNC($CALLARGSCTOCPP);
	$POSTRET
}
]]
	end
	return codegen.apply_functemp(func, temp)
end)

local function cppdecl(func)
	local doc = func.comments
	if not doc and func.comment then
		doc = { func.comment }
	end
	if doc then
		local cname
		if not func.cpponly then
			if func.multicfunc then
				cname = {}
				for _, name in ipairs(func.multicfunc) do
					cname[#cname+1] = "bgfx_" .. name
				end
			else
				cname = "bgfx_" .. func.cname
			end
		end
		doc = codegen.doxygen_type(doc, func, cname)
	end
	local funcdecl = codegen.apply_functemp(func, "$RET $FUNCNAME($ARGS)$CONST;\n")
	if doc then
		return doc .. "\n" .. funcdecl
	else
		return funcdecl
	end
end

function funcgen.cppdecl(func)
	-- Don't generate member functions here
	if not func.class and not func.conly then
		return cppdecl(func)
	end
end

-- c99decl is now built dynamically in codes() using naming

local typegen = {}

local function add_doxygen(typedef, define, cstyle, cname)
		local func = cstyle and codegen.doxygen_ctype or codegen.doxygen_type
		local doc = func(typedef.comments, typedef, cname or typedef.cname)
		if doc then
			return doc .. "\n" .. define
		else
			return define
		end
end

function typegen.consts(typedef)
	if typedef.const_value then
		return add_doxygen(typedef, codegen.gen_const_define(typedef), false, "bgfx_" .. typedef.cname)
	end
end

function typegen.cconsts(typedef)
	if typedef.const_value then
		return add_doxygen(typedef, codegen.gen_const_cdefine(typedef), true)
	end
end

function typegen.enums(typedef)
	if typedef.enum then
		return add_doxygen(typedef, codegen.gen_enum_define(typedef), false, "bgfx_" .. typedef.cname)
	end
end

function typegen.cenums(typedef)
	if typedef.enum then
		return add_doxygen(typedef, codegen.gen_enum_cdefine(typedef), true)
	end
end

function typegen.cflags(typedef)
	if typedef.flag then
		return add_doxygen(typedef, codegen.gen_flag_cdefine(typedef), true)
	end
end

function typegen.structs(typedef)
	if typedef.struct and not typedef.namespace then
		local methods = typedef.methods
		if methods then
			local m = {}
			for _, func in ipairs(methods) do
				if not func.conly then
					m[#m+1] = cppdecl(func)
				end
			end
			methods = m
		end
		return add_doxygen(typedef, codegen.gen_struct_define(typedef, methods))
	end
end

function typegen.cstructs(typedef)
	if typedef.struct then
		return add_doxygen(typedef, codegen.gen_struct_cdefine(typedef), true)
	end
end

function typegen.handles(typedef)
	if typedef.handle then
		return codegen.gen_handle(typedef)
	end
end

function typegen.chandles(typedef)
	if typedef.handle then
		return codegen.gen_chandle(typedef)
	end
end

function typegen.ids(typedef)
	if typedef.id then
		return codegen.gen_id(typedef)
	end
end

function typegen.cids(typedef)
	if typedef.id then
		return codegen.gen_cid(typedef)
	end
end

function typegen.funcptrs(typedef)
	if typedef.args then
		return add_doxygen(typedef, codegen.gen_funcptr(typedef))
	end
end

function typegen.cfuncptrs(typedef)
	if typedef.args then
		return add_doxygen(typedef, codegen.gen_cfuncptr(typedef), true)
	end
end

function typegen.cswitches(typedef)
	if typedef.cases then
		return add_doxygen(typedef, codegen.gen_cswitches(typedef), true)
	end
end

local function codes(idl, naming)
	local temp = {}
	for k in pairs(func_actions) do
		temp[k] = {}
	end

	for k in pairs(type_actions) do
		temp[k] = {}
	end

	-- Build c99decl template from naming
	local c99decl_template = naming.api_macro .. " $CRET " .. naming.L_ .. "$CFUNCNAME($CARGS);"

	-- call actions with func
	for _, f in ipairs(idl.funcs) do
		-- c99decl: generate function declaration with naming prefix
		local doc = f.comments
		if not doc and f.comment then
			doc = { f.comment }
		end
		if doc then
			doc = codegen.doxygen_ctype(doc, f)
		end
		local funcdecl = codegen.apply_functemp(f, c99decl_template)
		local decl
		if doc then
			decl = "\n" .. doc .. "\n" .. funcdecl
		else
			decl = funcdecl
		end
		table.insert(temp.c99decl, decl)

		for k in pairs(func_actions) do
			if k ~= "c99decl" then
				local fgen = funcgen[k]
				if fgen then
					table.insert(temp[k], (fgen(f)))
				end
			end
		end
	end

	-- call actions with type

	for _, typedef in ipairs(idl.types) do
		for k in pairs(type_actions) do
			local typegen = typegen[k]
			if typegen then
				table.insert(temp[k], (typegen(typedef)))
			end
		end
	end

	for k, indent in pairs(func_actions) do
		temp[k] = table.concat(temp[k], indent)
	end
	for k, indent in pairs(type_actions) do
		temp[k] = table.concat(temp[k], indent)
	end

	temp.version = string.format("#define " .. naming.U .. "_API_VERSION UINT32_C(%d)", idl._version or 0)

	return temp
end


local function add_path(filename)
	local path
	if type(paths) == "string" then
		path = paths
	else
		path = assert(paths[filename])
	end
	return path .. "/" .. filename
end

local function change_indent(str, indent)
	if indent == "\t" then
		-- strip trailing space only
		return (str:gsub("(.-)\n", function (line)
			return line:gsub("([ \t]*)$","\n") end))
	else
		return (str:gsub("(.-)\n", function (line)
			return line:gsub("^(\t*)(.-)[ \t]*$",
				function (tabs, content)
					return indent:rep(#tabs) .. content .. "\n"
				end)
		end))
	end
end

local gen = {}

function gen.apply(idl, tempfile, naming)
	local f = assert(io.open(tempfile, "rb"))
	local temp = f:read "a"
	f:close()
	local codes_tbl = codes(idl, naming)
	codes_tbl.source = tempfile
	return (temp:gsub("$([%l%d_]+)", codes_tbl))
end

function gen.gen(idl, tempfile, outputfile, indent, naming)
	local codes = gen.apply(idl, tempfile, naming)
	codes = change_indent(codes, indent)

	return codes
end

return gen.gen
