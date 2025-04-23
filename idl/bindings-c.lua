local gen = {}

function gen.gen(idl, converter_config, templete, indent)
    local converter = require "converter-c"
    local codes = converter.convert(idl, converter_config)
    local generator = require "generator"
    return generator.gen(codes, templete, indent)
end

return gen