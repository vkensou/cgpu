local gen = {}

function gen.apply(templete, codes)
	return (templete:gsub("$([%l%d_]+)", codes))
end

local function change_indent(str, indent)
	if indent == "\t" then
		-- strip trailing space only
		return (str:gsub("(.-)\n", function (line)
			return line:gsub("([ \t]*)$","\n") end))
	else
		return (str:gsub("(.-)\n", function (line)
			return line:gsub("^(\t*)(.-)[ \t]*$",
				function (tabs, content)
					return indent:rep(#tabs) .. content .. "\n"
				end)
		end))
	end
end

function gen.gen(codes, templete, indent)
	codes = gen.apply(templete, codes)
	codes = change_indent(codes, indent)

    return codes
end

return gen