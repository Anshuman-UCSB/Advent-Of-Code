def main(input):
	lines = input.splitlines()
	total = 0
	total_2 = 0
	for line in lines:
		digits = [char for char in line if char.isnumeric()]
		if digits:
			total += int(digits[0]+digits[-1])

		digits = [char for char in translate(line) if char.isnumeric()]
		total_2 += int(digits[0]+digits[-1])
	print(translate("eightwo2twothree"))
	return total, total_2

def translate(line):
	return (line
		.replace("one", "one1one")
		.replace("two", "two2two")
		.replace("three", "three3three")
		.replace("four", "four4four")
		.replace("five", "five5five")
		.replace("six", "six6six")
		.replace("seven", "seven7seven")
		.replace("eight", "eight8eight")
		.replace("nine", "nine9nine")
		.replace("zero", "zero0zero")
	)