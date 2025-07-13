-- Copyright 2019 云风 https://github.com/cloudwu . All rights reserved.
-- License (the same with bgfx) : https://github.com/bkaradzic/bgfx/blob/master/LICENSE

local gen = require "cgpu-codegen"

local path = (...)

local files = {
	{ temp = "temp.cgpu.h" , output = "../src/cgpu/include/cgpu/api.h", indent = "    " },
}

for _, f in ipairs (files) do
	local output = f.output
	if path then
		output = output:gsub(".-(/[^/]+)$", path .. "%1")
	end
	gen.gen(f.temp, output, f.indent or "\t")
end
