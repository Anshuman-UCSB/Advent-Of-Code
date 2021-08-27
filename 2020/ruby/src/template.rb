template = "module Day%02d
	class Day
		def part1(input)
			
		end

		def part2(input)
			nil
		end

		def run(input)
			[part1(input), part2(input)]
		end
	end
end"
for i in 1 ... 26
	File.open("day%02d.rb" % i, 'w') {|f| f.write template % i}
	File.open("../input/day%02d.txt" % i, 'w')
end