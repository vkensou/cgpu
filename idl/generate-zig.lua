-- Copyright 2019 云风 https://github.com/cloudwu . All rights reserved.
-- License (the same with bgfx) : https://github.com/bkaradzic/bgfx/blob/master/LICENSE

local gen = require "bindings-zig"

local codes = gen.gen()
gen.write(codes, "../bindings/zig/cgpu.zig")
