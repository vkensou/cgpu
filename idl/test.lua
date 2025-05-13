-- Copyright 2019 云风 https://github.com/cloudwu . All rights reserved.
-- License (the same with bgfx) : https://github.com/bkaradzic/bgfx/blob/master/LICENSE

local path = (...)

local loader = require "idl-loader"
local idl = loader("cgpu.idl")

local function readfile(path)
	local f = assert(io.open(path, "rb"))
	local content = f:read "a"
	f:close()
	return content
end

local function writefile(path, content)
	local out = assert(io.open(path, "wb"))
	out:write(content)
	out:close()
end

local converts = {
	{ bindings = require "bindings-c", tempfile = "temp.cgpu.h", outputfile = "./enums.h", indent = "    " },
	{ bindings = require "bindings-zig", tempfile = "temp.cgpu.zig", outputfile = "./cgpu.zig", indent = "    " },
}

for _, c in ipairs(converts) do
	print ("Generate", c.outputfile, "from", c.tempfile)
	local output = c.bindings.gen(idl, {}, readfile(c.tempfile), c.indent or "\t")
	writefile(c.outputfile, output)
end