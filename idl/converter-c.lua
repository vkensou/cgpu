local base_converter = require "converter"

local DEFAULT_NAME_ALIGN = 20
local DEFINE_NAME_ALIGN  = 41

local function namealign(name, align)
	align = align or DEFAULT_NAME_ALIGN
	return string.rep(" ", align - #name)
end

local function camelcase_to_underscorecase(name)
	local tmp = {}
	for v in name:gmatch "[%u%d]+%l*" do
		tmp[#tmp+1] = v:lower()
	end
	return table.concat(tmp, "_")
end

local function to_underscorecase(name)
	local tmp = {}
	for v in name:gmatch "[_%u][%l%d]*" do
		if v:byte() == 95 then	-- '_'
			v = v:sub(2)	-- remove _
		end
		tmp[#tmp+1] = v
	end
	return table.concat(tmp, "_")
end

local function underscorecase_to_camelcase(name)
	local tmp = {}
	for v in name:gmatch "[^_]+" do
		tmp[#tmp+1] = v:sub(1,1):upper() .. v:sub(2)
	end
	return table.concat(tmp)
end

local name_converter = {}

function name_converter.enum_name(enum)
    return "cgpu_" .. camelcase_to_underscorecase(enum.name)
end

function name_converter.enum_item_name(enum, enum_new_name, item)
    return "CGPU_" .. (to_underscorecase(enum.name) .. "_" .. camelcase_to_underscorecase(item.name)):upper()
end

function name_converter.flag_name(flag)
    return "cgpu_" .. camelcase_to_underscorecase(flag.name)
end

function name_converter.flag_item_name(flag, flag_new_name, item)
    return "CGPU_" .. (to_underscorecase(flag.name) .. "_" .. camelcase_to_underscorecase(item.name)):upper()
end

local enum_temp = [[
typedef enum $NAME
{
    $ITEMS
    
    $COUNT
    
} $NAME_enum;
]]

local function gen_enum_cdefine(enum, enum_temp)
	assert(type(enum.enum) == "table", "Not an enum")
	local cname = enum.name
	local uname = cname:upper()
	local items = {}
	for index , item in ipairs(enum.enum) do
		local comment = ""
		if item.comment then
			comment = table.concat(item.comment, " ")
		end
		local name = item.name
		items[#items+1] = string.format("%s,%s /** (%2d) %s%s */",
			name,
			namealign(name, 40),
			index - 1,
			comment,
			namealign(comment, 30))
	end

	local temp = {
		NAME = cname,
		COUNT = uname .. "_COUNT",
		ITEMS = table.concat(items, "\n\t"),
	}

	return (enum_temp:gsub("$(%u+)", temp))
end

local flag_temp = [[
typedef enum $NAME
{
    $ITEMS
        
} $NAME_flag;
]]

local function gen_flag_cdefine(flag, flag_temp)
	assert(type(flag.flag) == "table", "Not a flag")

	local cname = flag.name
	local s = {}
	local shift = flag.shift
	for index, item in ipairs(flag.flag) do
		local name = item.name
		local value = item.value

		-- combine flags
		if #item > 0 then
			if item.comment then
				for _, c in ipairs(item.comment) do
					s[#s+1] = "/// " .. c
				end
			end
			local sets = {}
			for _, v in ipairs(item) do
				sets[#sets+1] = v
			end
			s[#s+1] = string.format("%s = %s,", 
				name, table.concat(sets, " | "))
		else
			local comment = ""
			if item.comment then
				if #item.comment > 1 then
					s[#s+1] = ""
					for _, c in ipairs(item.comment) do
						s[#s+1] = "/// " .. c
					end
				else
					comment = " //!< " .. item.comment[1]
				end
			end
			value = string.format(flag.format, value)
			local code = string.format("%s = 0x%s,%s /** (%2d) %s%s */",
				name,
				value,
				namealign(name, 40),
				index - 1,
				comment,
				namealign(comment, 30))
			
			s[#s+1] = code
		end
	end

	local mask
	if flag.mask then
		mask = string.format(flag.format, flag.mask)
		mask = string.format("UINT%d_C(0x%s)", flag.bits, mask)
	end

	if shift then
		local name = cname .. "_SHIFT"
		local comment = flag.desc or ""
		local shift_align = tostring(shift)
		shift_align = shift_align .. namealign(shift_align, #mask)
		local comment = ""
		if flag.desc then
			comment = string.format(" //!< %s bit shift", flag.desc)
		end
		local code = string.format("#define %s %s%s%s", name, namealign(name, DEFINE_NAME_ALIGN), shift_align, comment)
		s[#s+1] = code
	end
	if flag.range then
		local name = cname .. "_MASK"
		local comment = ""
		if flag.desc then
			comment = string.format(" //!< %s bit mask", flag.desc)
		end
		local code = string.format("#define %s %s%s%s", name, namealign(name, DEFINE_NAME_ALIGN), mask, comment)
		s[#s+1] = code
	end

	if flag.helper then
		s[#s+1] = string.format(
			"#define %s(v) ( ( (uint%d_t)(v)<<%s )&%s)",
			cname,
			flag.bits,
			(cname .. "_SHIFT"),
			(cname .. "_MASK"))
	end

	local temp = {
		NAME = cname,
		ITEMS = table.concat(s, "\n\t"),
	}

	return (flag_temp:gsub("$(%u+)", temp))
end

local printer = {}

local function add_doxygen(typedef, define, cstyle, cname)
    return define
end

function printer.enums(typedef)
	if typedef.enum then
		return add_doxygen(typedef, gen_enum_cdefine(typedef, enum_temp), true)
	end
end

function printer.flags(typedef)
	if typedef.flag then
		return add_doxygen(typedef, gen_flag_cdefine(typedef, flag_temp), true)
	end
end

function printer.structs(typedef)
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

function printer.handles(typedef)
	if typedef.handle then
		return codegen.gen_handle(typedef)
	end
end

function printer.funcptrs(typedef)
	if typedef.args then
		return add_doxygen(typedef, codegen.gen_funcptr(typedef))
	end
end

local converter = {}

function converter.convert(idl, config)
    local converter = name_converter
    local printer = printer
    local converted = base_converter.codes(converter, idl)
    return base_converter.print_code(printer, converted)
end

return converter