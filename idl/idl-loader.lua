local idl = require "idl"
local doxygen = require "doxygen"
local idlfile = {}

local function calc_flag_values(flag)
	local shift = flag.shift
	local base = flag.base or 0
	local cap = 1 << (flag.range or 0)

	if flag.range then
		if flag.range == 64 then
			flag.mask = 0xffffffffffffffff
		else
			flag.mask = ((1 << flag.range) - 1) << shift
		end
	end

	local values = {}
	for index, item in ipairs(flag.flag) do
		local value = item.value
		if flag.const then
			-- use value directly
		elseif shift then
			if value then
				if value > 0 then
					value = value - 1
				end
			else
				value = index + base - 1
			end
			if value >= cap then
				error (string.format("Out of range for %s.%s (%d/%d)", flag.name, item.name, value, cap))
			end
			value = value << shift
		elseif #item == 0 then
			if value then
				if value > 0 then
					value = 1 << (value - 1)
				end
			else
				local s = index + base - 2
				if s >= 0 then
					value = 1 << s
				else
					value = 0
				end
			end
		end
		if not value then
			-- It's a combine flags
			value = 0
			for _, name in ipairs(item) do
				local v = values[name]
				if v then
					value = value | v
				else
					-- todo : it's a undefined flag
					value = nil
					break
				end
			end
		end
		item.value = value
		values[item.name] = value
	end
end

local function convert_arg(all_types, arg, namespace)
	local fulltype, array = arg.fulltype:match "(.-)%s*(%[%s*[%d%a_:]*%s*%])"
	if array then
		arg.fulltype = fulltype
		arg.array = array
		local enum, value = array:match "%[%s*([%a%d]+)::([%a%d]+)%]"
		if enum then
			local typedef = all_types[ enum .. "::Enum" ]
			if typedef == nil then
				error ("Unknown Enum " .. enum)
			end
			arg.carray = "[BGFX_" .. camelcase_to_underscorecase(enum):upper() .. "_" .. value:upper() .. "]"
		end
	end
	local t, postfix = arg.fulltype:match "(%a[%a%d_:]*)%s*([*&]+)%s*$"
	if t then
		arg.type = t
		if postfix == "&" then
			arg.ref = true
		end
	else
		local prefix, t = arg.fulltype:match "^%s*(%a+)%s+(%S+)"
		if prefix then
			arg.type = t
		else
			arg.type = arg.fulltype
		end
	end
	local ctype
	local substruct = namespace.substruct
	if substruct then
		ctype = substruct[arg.type]
	end
	if not ctype then
		ctype = all_types[arg.type]
	end
	if not ctype then
		error ("Undefined type " .. arg.fulltype .. " in " .. namespace.name)
	end
	arg.ctype = arg.fulltype:gsub(arg.type, ctype.name):gsub("&", "*")
	if ctype.name ~= arg.type then
		arg.cpptype = arg.fulltype:gsub(arg.type, "bgfx::"..arg.type)
	else
		arg.cpptype = arg.fulltype
	end
	if arg.ref then
		arg.ptype = arg.cpptype:gsub("&", "*")
	end
end

local function nameconversion(all_types, all_funcs)
	for _,v in ipairs(all_types) do
		local name = v.name
		local cname = v.cname
		if cname == nil then
			if name:match "^%u" then
				cname = (name)
			elseif not v.flag then
				v.cname = name
			end
		end
		if cname and not v.flag then
			if v.namespace then
				cname = (v.namespace) .. "_" .. cname
			end
			v.cname = cname .. "_t"
		end
		if v.enum then
			v.typename = v.name
			v.name = v.name .. "::Enum"
		end
		if v.flag then
			calc_flag_values(v)
		end
	end

	-- make index
	for _,v in ipairs(all_types) do
		if not v.namespace then
			if all_types[v.name] then
				error ("Duplicate type " .. v.name)
			elseif not v.flag then
				all_types[v.name] = v
			end
		end
	end

	-- make sub struct index
	for _,v in ipairs(all_types) do
		if v.namespace then
			local super = all_types[v.namespace]
			if not super then
				error ("Define " .. v.namespace .. " first")
			end
			local substruct = super.substruct
			if not substruct then
				substruct = {}
				super.substruct = substruct
			end
			if substruct[v.name] then
				error ( "Duplicate sub struct " .. v.name .. " in " .. v.namespace)
			end
			v.parent_class = super
			substruct[#substruct+1] = v
			substruct[v.name] = v
		end
	end

	for _,v in ipairs(all_types) do
		if v.struct then
			for _, item in ipairs(v.struct) do
				convert_arg(all_types, item, v)
			end
		elseif v.args then
			-- funcptr
			for _, arg in ipairs(v.args) do
				convert_arg(all_types, arg, v)
			end
			convert_vararg(v)
			convert_arg(all_types, v.ret, v)
		end
	end

	local funcs = {}
	local funcs_conly = {}
	local funcs_alter = {}

	for _,v in ipairs(all_funcs) do
		if v.cname == nil then
			v.cname = convert_funcname(v.name)
		end
		if v.class then
			v.cname = convert_funcname(v.class) .. "_" .. v.cname
			local classtype = all_types[v.class]
			if classtype then
				local methods = classtype.methods
				if not methods then
					methods = {}
					classtype.methods = methods
				end
				methods[#methods+1] = v
			end
		elseif not v.conly then
			funcs[v.name] = v
		end

		if v.conly then
			table.insert(funcs_conly, v)
		end

		for _, arg in ipairs(v.args) do
			convert_arg(all_types, arg, v)
			gen_arg_conversion(all_types, arg)
		end
		convert_vararg(v)
		if v.alter_name then
			funcs_alter[#funcs_alter+1] = v
		end
		convert_arg(all_types, v.ret, v)
		gen_ret_conversion(all_types, v)
		local namespace = v.class
		if namespace then
			local classname = namespace
			if v.const then
				classname = "const " .. classname
			end
			local classtype = { fulltype = classname .. "*" }
			convert_arg(all_types, classtype, v)
			v.this = classtype.ctype
			v.this_type = classtype
			v.this_conversion = string.format( "%s This = (%s)_this;", classtype.cpptype, classtype.cpptype)
			v.this_to_c = string.format("(%s)this", classtype.ctype)
		end
	end

	for _, v in ipairs(funcs_conly) do
		local func = funcs[v.name]
		if func then
			func.multicfunc = func.multicfunc or { func.cname }
			table.insert(func.multicfunc, v.cname)
		end
	end

	for _, v in ipairs(funcs_alter) do
		local func = funcs[v.alter_name]
		v.alter_cname = func.cname
	end
end

local function postprocess(all_types, all_funcs)
    for _, v in ipairs(all_types) do
        if v.flag then
            calc_flag_values(v)
        end
    end

    -- make index
    for _, v in ipairs(all_types) do
        if not v.namespace then
            if all_types[v.name] then
                error("Duplicate type " .. v.name)
            elseif not v.flag then
                all_types[v.name] = v
            end
        end
    end

    -- make sub struct index
    for _, v in ipairs(all_types) do
        if v.namespace then
            local super = all_types[v.namespace]
            if not super then
                error("Define " .. v.namespace .. " first")
            end
            local substruct = super.substruct
            if not substruct then
                substruct = {}
                super.substruct = substruct
            end
            if substruct[v.name] then
                error("Duplicate sub struct " .. v.name .. " in " .. v.namespace)
            end
            v.parent_class = super
            substruct[#substruct + 1] = v
            substruct[v.name] = v
        end
    end

    for _, v in ipairs(all_types) do
        if v.struct then
            for _, item in ipairs(v.struct) do
                convert_arg(all_types, item, v)
            end
        elseif v.args then
            -- funcptr
            for _, arg in ipairs(v.args) do
                convert_arg(all_types, arg, v)
            end
            convert_vararg(v)
            convert_arg(all_types, v.ret, v)
        end
    end

    local funcs = {}
    local funcs_conly = {}
    local funcs_alter = {}

    for _, v in ipairs(all_funcs) do
        if v.cname == nil then
            v.cname = convert_funcname(v.name)
        end
        if v.class then
            v.cname = convert_funcname(v.class) .. "_" .. v.cname
            local classtype = all_types[v.class]
            if classtype then
                local methods = classtype.methods
                if not methods then
                    methods = {}
                    classtype.methods = methods
                end
                methods[#methods + 1] = v
            end
        elseif not v.conly then
            funcs[v.name] = v
        end

        if v.conly then
            table.insert(funcs_conly, v)
        end

        for _, arg in ipairs(v.args) do
            convert_arg(all_types, arg, v)
            gen_arg_conversion(all_types, arg)
        end
        convert_vararg(v)
        if v.alter_name then
            funcs_alter[#funcs_alter + 1] = v
        end
        convert_arg(all_types, v.ret, v)
        gen_ret_conversion(all_types, v)
        local namespace = v.class
        if namespace then
            local classname = namespace
            if v.const then
                classname = "const " .. classname
            end
            local classtype = {
                fulltype = classname .. "*"
            }
            convert_arg(all_types, classtype, v)
            v.this = classtype.ctype
            v.this_type = classtype
            v.this_conversion = string.format("%s This = (%s)_this;", classtype.cpptype, classtype.cpptype)
            v.this_to_c = string.format("(%s)this", classtype.ctype)
        end
    end

    for _, v in ipairs(funcs_conly) do
        local func = funcs[v.name]
        if func then
            func.multicfunc = func.multicfunc or {func.cname}
            table.insert(func.multicfunc, v.cname)
        end
    end

    for _, v in ipairs(funcs_alter) do
        local func = funcs[v.alter_name]
        v.alter_cname = func.cname
    end
end

local function doload(filename)
    assert(conversion == nil, "Don't call loader.load() after loader.idl()")
    assert(idlfile[filename] == nil, "Duplicate load " .. filename)
    local source = doxygen.load(filename)

    local f = assert(load(source, filename, "t", idl))
    f()
    idlfile[filename] = true
end

local function loader(filename)
    if filename and not idlfile[filename] then
        doload(filename)
    end
    assert(next(idlfile), "call loader.load() first")

    postprocess(idl.types, idl.funcs)
	
    return idl
end

return loader
