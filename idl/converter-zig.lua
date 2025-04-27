local base_converter = require "converter"

local function Set(list)
    local set = {}
    for _, l in ipairs(list) do
        set[l] = true
    end
    return set
end

local DEFAULT_NAME_ALIGN = 20
local DEFINE_NAME_ALIGN = 41

local function namealign(name, align)
    align = align or DEFAULT_NAME_ALIGN
    return string.rep(" ", align - #name)
end

local function upperCamelcase_to_underscorecase(name)
	local tmp = {}
	for v in name:gmatch "[%u%d]+[%l%d]*" do
		tmp[#tmp+1] = v:lower()
	end
	return table.concat(tmp, "_")
end

local function lowerCamelcase_to_underscorecase(name)
	local tmp = {}
	for v in name:gmatch "[%u%l%d]+[%l%d]*" do
		tmp[#tmp+1] = v:lower()
	end
	return table.concat(tmp, "_")
end

local function to_underscorecase(name)
    local tmp = {}
    for v in name:gmatch "[_%u][%l%d]*" do
        if v:byte() == 95 then -- '_'
            v = v:sub(2) -- remove _
        end
        tmp[#tmp + 1] = v
    end
    return table.concat(tmp, "_")
end

local function underscorecase_to_camelcase(name)
    local tmp = {}
    for v in name:gmatch "[^_]+" do
        tmp[#tmp + 1] = v:sub(1, 1):upper() .. v:sub(2)
    end
    return table.concat(tmp)
end

local keywords = Set {"error", "opaque", "export"}

local function handle_embed_keyword(name)
    if keywords[name] or name:match("^%d") then
        return '@"' .. name .. '"'
    else
        return name
    end
end

local name_converter = {}

name_converter.flat_combined_flag = true

function name_converter.enum_name(enum)
    return enum.name
end

function name_converter.enum_item_name(enum, enum_new_name, item)
    return handle_embed_keyword(upperCamelcase_to_underscorecase(item.name))
end

function name_converter.flag_name(flag)
    return flag.name
end

function name_converter.flag_item_name(flag, flag_new_name, item)
    return handle_embed_keyword(upperCamelcase_to_underscorecase(item.name))
end

function name_converter.struct_name(struct)
	return struct.name
end

function name_converter.struct_item_name(struct, struct_new_name, item)
	return lowerCamelcase_to_underscorecase(item.name)
end

local enum_temp = [[
pub const $NAME = enum(u32) {
    $ITEMS
};
]]

local function gen_enum_cdefine(enum, enum_temp)
    assert(type(enum.enum) == "table", "Not an enum")
    local cname = enum.name
    local items = {}
    for index, item in ipairs(enum.enum) do
        local comment = ""
        if item.comment then
            comment = table.concat(item.comment, " ")
        end
        local name = item.name
        items[#items + 1] = string.format("%s, // (%2d) %s%s", name, index - 1, comment, namealign(comment, 30))
    end

    local temp = {
        NAME = cname,
        ITEMS = table.concat(items, "\n\t")
    }

    return (enum_temp:gsub("$(%u+)", temp))
end

local flag_temp = [[
pub const $NAME = packed struct(u32) {
    $ITEMS  
};
]]

local function gen_flag_cdefine(flag, flag_temp)
    assert(type(flag.flag) == "table", "Not a flag")

    local cname = flag.name
    local s = {}
    local shift = flag.shift
    local used = 0
    for index, item in ipairs(flag.flag) do
        local name = item.name
        local value = item.value

        -- combine flags
        if #item == 0 then
            local comment = ""
            if item.comment then
                if #item.comment > 1 then
                    s[#s + 1] = ""
                    for _, c in ipairs(item.comment) do
                        s[#s + 1] = "/// " .. c
                    end
                else
                    comment = " //!< " .. item.comment[1]
                end
            end
            value = string.format(flag.format, value)
            local code = string.format("%s: bool = false, // (%2d) %s%s", name, index - 1, comment,
                namealign(comment, 30))

            used = used + 1
            s[#s + 1] = code
        end
    end

    if used < 32 then
        s[#s + 1] = string.format("padding: u%d = 0,", 32 - used)
    end

    for index, item in ipairs(flag.flag) do
        local name = item.name
        local value = item.value

        -- combine flags
        if #item > 0 then
            if item.comment then
                for _, c in ipairs(item.comment) do
                    s[#s + 1] = "/// " .. c
                end
            end
            local sets = {}
            for _, v in ipairs(item) do
                sets[#sets + 1] = "." .. v .. " = true"
            end
            s[#s + 1] = string.format("const %s: %s = .{ %s };", name, cname, table.concat(sets, ", "))
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
        s[#s + 1] = code
    end
    if flag.range then
        local name = cname .. "_MASK"
        local comment = ""
        if flag.desc then
            comment = string.format(" //!< %s bit mask", flag.desc)
        end
        local code = string.format("#define %s %s%s%s", name, namealign(name, DEFINE_NAME_ALIGN), mask, comment)
        s[#s + 1] = code
    end

    if flag.helper then
        s[#s + 1] = string.format("#define %s(v) ( ( (uint%d_t)(v)<<%s )&%s)", cname, flag.bits, (cname .. "_SHIFT"),
            (cname .. "_MASK"))
    end

    local temp = {
        NAME = cname,
        ITEMS = table.concat(s, "\n\t")
    }

    return (flag_temp:gsub("$(%u+)", temp))
end

local function gen_struct_cdefine(struct)
    return ""
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
	if typedef.struct then
		return add_doxygen(typedef, gen_struct_cdefine(typedef), true)
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
