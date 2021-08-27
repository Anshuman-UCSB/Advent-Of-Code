module Day01
	class Day
		def part1(input)
			input.each_with_index do |v, i|
				input[i..-1].each_with_index do |k, j|
					if v+k == 2020
						return v*k
					end
				end
			end
		end

		def part2(input)
			input.each_with_index do |v, i|
				input[i..-1].each_with_index do |k, j|
					input[j..-1].each do |m|
						if v+k+m == 2020
							return v*k*m
						end
					end
				end
			end
		end

		def run(input)
			input.map!(&:to_i).sort!
			[part1(input), part2(input)]
		end
	end
end