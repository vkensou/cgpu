-- Copyright 2019 云风 https://github.com/cloudwu . All rights reserved.
-- License (the same with bgfx) : https://github.com/bkaradzic/bgfx/blob/master/LICENSE

local gen = require "bindings-c"

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

local bindinds_c = require "bindings-c"

local tempfile = "temp.cgpu.h"
local outputfile = "./cgpu.h"
local indent = "    "

print ("Generate", outputfile, "from", tempfile)
local output = bindinds_c.gen(idl, {}, readfile(tempfile), indent or "\t")
writefile(outputfile, output)