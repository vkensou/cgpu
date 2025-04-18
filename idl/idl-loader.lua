local idl = require "idl"
local doxygen = require "doxygen"
local idlfile = {}

local function doload(filename)
	assert(conversion == nil, "Don't call loader.load() after loader.idl()")
	assert(idlfile[filename] == nil, "Duplicate load " .. filename)
	local source = doxygen.load(filename)

	local f = assert(load(source, filename , "t", idl))
	f()
	idlfile[filename] = true
end

local function loader(filename)
	if conversion == nil then
		if filename and not idlfile[filename] then
			doload(filename)
		end
		assert(next(idlfile), "call loader.load() first")
	end
	return idl
end

return loader
