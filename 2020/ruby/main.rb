if ARGV.length > 1
	raise "Invalid arguments, either enter nothing for all days, or a specific day number."
end
for day in 1...26
	eval("require \"./src/day%02d.rb\"" % day)
	eval("include Day%02d" % day)
end

days = [
		Day01::Day.new, 
		Day02::Day.new,
		Day03::Day.new,
		Day04::Day.new,
		Day05::Day.new,
		Day06::Day.new,
		Day07::Day.new,
		Day08::Day.new,
		Day09::Day.new,
		Day10::Day.new,
		Day11::Day.new, 
		Day12::Day.new,
		Day13::Day.new,
		Day14::Day.new,
		Day15::Day.new,
		Day16::Day.new,
		Day17::Day.new,
		Day18::Day.new,
		Day19::Day.new,
		Day20::Day.new,
		Day21::Day.new, 
		Day22::Day.new,
		Day23::Day.new,
		Day24::Day.new,
		Day25::Day.new
	]
def printResult(results)
	puts "[P1] #{results[0]}"
	puts "[P2] #{results[1]}"
end
if ARGV.length == 0
	days.each_with_index do |x, i|
		puts "\n\tDay #{i+1}:"
		printResult(x.run File.open("input/day%02d.txt" % ARGV[0]).readlines.map(&:chomp))
	end
else
	if 1 <= ARGV[0].to_i and ARGV[0].to_i<=25
		puts "\tDay #{ARGV[0]}:"
		printResult(days[ARGV[0].to_i-1].run File.open("input/day%02d.txt" % ARGV[0]).readlines.map(&:chomp))
	else
		raise "Invalid day"
	end
end