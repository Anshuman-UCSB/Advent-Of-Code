module Day02
	class Day
		def part1(input)
			out = 0
			input.each {|line|
				spl = line.split(/[- :]+/)
				v = spl[-1].count(spl[-2])
				if spl[0].to_i<=v && v<=spl[1].to_i
					out+=1
				end
			}
			return out
		end

		def part2(input)
			out = 0
			input.each {|line|
				spl = line.split(/[- :]+/)
				if (spl[-1][spl[0].to_i-1]==spl[-2]) ^ (spl[-1][spl[1].to_i-1]==spl[-2])
					out+=1
				end
			}
			return out
		end

		def run(input)
			[part1(input), part2(input)]
		end
	end
end