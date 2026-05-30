-- generate-binding.lua
-- Unified code generation entry point.
-- Usage: lua generate-binding.lua <idl_path> <template_path> <binding> <output_path> [indent]
--   binding: module suffix for "bindings-<binding>" (e.g. "c" → bindings-c, "zig" → bindings-zig)
--   indent : optional, defaults to "\t"

local idl_path      = arg[1]
local template_path = arg[2]
local binding       = arg[3]
local output_path   = arg[4]
local indent        = arg[5]

if not idl_path or not binding or not output_path then
	error("Usage: lua generate-binding.lua <idl_path> <template_path> <binding> <output_path> [indent]")
end

local codegen = require "codegen"
local idl = codegen.idl(idl_path)

local modname = "bindings-" .. binding
local gen = require(modname)

-- Dispatch: C binding uses template-file API; others use gen()+write() convention

print ("Generating: ", output_path, "from", template_path)

local codes = gen(idl, template_path, output_path, indent or "\t")

function changed(codes, outputfile)
	local out = io.open(outputfile, "rb")
	if out then
		local origin = out:read "a"
		out:close()
		return origin ~= codes
	end
	return true
end

if not changed(codes, output_path) then
	print("No change")
else
	local out = assert(io.open(output_path, "wb"))
	out:write(codes)
	out:close()
	print("Output: " .. output_path)
end
