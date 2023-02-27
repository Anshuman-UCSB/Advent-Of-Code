def day1(input):
	input+=input[0]
	return [sum(input[i]==input[i+1] for i in range(len(input)-1)),None]