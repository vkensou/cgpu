local gen = {}

function gen.gen(idlfile, converter_config, templete, indent)
    local generator = require "generator"
    local converter = require "converter-c"
    local codes = converter.convert(idl, converter_config)
    return generator.gen(codes, templete, indent)
end

return gen