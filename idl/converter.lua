local func_actions = {

    c99 = "\n",
    c99decl = "\n",
    cppdecl = "\n",
    interface_struct = "\n\t",
    interface_import = ",\n\t\t\t",
    c99_interface = "\n",
    cpp_interface = "\n",
    c99_functionid = "\n\t",
    cpp_functionid = "\n\t\t"
}

local type_actions = {
    flags = "\n",
    enums = "\n",
    structs = "\n",
    handles = "\n",
    funcptrs = "\n"
}

local typegen = {}

function typegen.enum(name_converter, enum)
    local temp = {}
    temp.name = name_converter.enum_name(enum)
    temp.comment = enum.comment
    temp.enum = {}
    for index, item in ipairs(enum.enum) do
        temp.enum[index] = {
            name = name_converter.enum_item_name(enum, temp.name, item),
            comment = item.comment
        }
    end
    return temp
end

local function flag_format(flag)
    if not flag.format then
        return "%0" .. (flag.bits // 4) .. "x"
    else
        return flag.format
    end
end

local function find_old_flag_name(flag, old_name, new_flag)
    for i = 1, #flag.flag do
        if flag.flag[i].name == old_name then
            return new_flag.flag[i].name
        end
    end
    assert(false)
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

function typegen.flag(name_converter, flag)
    local temp = {}
    temp.name = name_converter.flag_name(flag)
    temp.base = flag.base
    temp.bits = flag.bits
    temp.format = flag_format(flag)
    temp.shift = flag.shift
    temp.desc = flag.desc
    temp.flag = {}
    for index, item in ipairs(flag.flag) do
        local new_item = {}
        for k, v in pairs(item) do
            if type(k) ~= "number" then
                new_item[k] = v
            end
        end
        new_item.name = name_converter.flag_item_name(flag, temp.name, item)
        temp.flag[index] = new_item
    end

    if name_converter.flat_combined_flag then
        for index, item in ipairs(flag.flag) do
            if #item > 0 then
                local added = {}
                for k, v in ipairs(item) do
                    flat_combined(flag, v, added)
                end

                local i = 1
                for k, _ in pairs(added) do
                    temp.flag[index][i] = find_old_flag_name(flag, k, temp)
                    i = i + 1
                end
            end
        end
    else
        for index, item in ipairs(flag.flag) do
            for k, v in ipairs(item) do
                temp.flag[index][k] = find_old_flag_name(flag, v, temp)
            end
        end
    end

    return temp
end

function typegen.struct(name_converter, struct)
    local temp = {}
    temp.name = name_converter.struct_name(struct)
    temp.struct = {}
    for index, item in pairs(struct.struct) do
        local new_item = {}
        new_item.name = name_converter.struct_item_name(struct, temp.name, item)
        new_item.type = item.type
        new_item.ctype = item.ctype
        new_item.fulltype = item.fulltype
        new_item.cpptype = item.cpptype
        temp.struct[index] = new_item
    end
    return temp
end

local function convert_arg(all_types, arg, namespace)
    local type = all_types[arg.type]
    if type ~= nil then
        arg.fulltype = type.name
    else
        arg.fulltype = arg.type
    end
end

local converter = {}

function converter.codes(name_converter, idl)
    local temp = {}

    temp.types = {}

    for i, typedef in ipairs(idl.types) do
        local new_item = nil
        if typedef.enum and type(typedef.enum) == "table" then
            new_item = typegen.enum(name_converter, typedef)
        elseif typedef.flag and type(typedef.flag) == "table" then
            new_item = typegen.flag(name_converter, typedef)
        elseif typedef.struct and type(typedef.struct) == "table" then
            new_item = typegen.struct(name_converter, typedef)
        end
        if new_item ~= nil then
            temp.types[i] = new_item
            temp.types[typedef.name] = new_item
        end
    end

    temp.funcs = {}

    for i,v in pairs(temp.types) do
        if type(i) == "number" then 
            if v.struct then
                for _, item in ipairs(v.struct) do
                    convert_arg(temp.types, item, v)
                end
            end
        end
    end

    return temp
end

function converter.print_code(code_printer, idl)
    local temp = {}
    for k in pairs(func_actions) do
        temp[k] = {}
    end

    for k in pairs(type_actions) do
        temp[k] = {}
    end

    -- call actions with func
    for _, f in pairs(idl.funcs) do
        for k in pairs(func_actions) do
            local funcgen = funcgen[k]
            if funcgen then
                table.insert(temp[k], (funcgen(f)))
            end
        end
    end

    -- call actions with type

    for i, typedef in pairs(idl.types) do
        if type(i) == "number" then
            for k in pairs(type_actions) do
                local printer = code_printer[k]
                if printer then
                    table.insert(temp[k], (printer(typedef)))
                end
            end
        end
    end

    for k, indent in pairs(func_actions) do
        temp[k] = table.concat(temp[k], indent)
    end
    for k, indent in pairs(type_actions) do
        temp[k] = table.concat(temp[k], indent)
    end

    temp.version = string.format("#define BGFX_API_VERSION UINT32_C(%d)", idl._version or 0)

    return temp
end

return converter
