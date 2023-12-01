digit_names = ["zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"]

def main(input):
	lines = input.splitlines()
	total1 = 0
	total2 = 0
	for line in lines:
		# digits = []
		# for char in line:
		# 	if char.isnumeric():
		# 		digits.append(char)
		digits = [char for char in line if char.isnumeric()]
		if digits:
			total1 += int(digits[0]+digits[-1])

		digits = [char for char in translate(line) if char.isnumeric()]
		total2 += int(digits[0]+digits[-1])

	return total1, total2

def translate(line):
	for num, name in enumerate(digit_names):
		line = line.replace(name, f"{name}{num}{name}")
	return line