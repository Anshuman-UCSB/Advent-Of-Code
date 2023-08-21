# this function is called by my runner program, so basically the input I am testing is passed in as a raw string
def main(input):
	p1 = 0
	p2 = 0
	# for each l(ine) in the input
	for l in input.splitlines():
		# if l is "1-3 a: abcde", then by splitting it on spaces we get
		# l.split(' ') = ["1-3", "a:","abcde"]
		# since this will always be a list with 3 elements, we can unpack it into variables, so in this case we get
		# nums = "1-3"
		# letter = "a:"
		# pw = "abcde"
		nums,letter,pw = l.split(' ')
		# for nums ("1-3") I want to somehow extract the numbers 1 and 3
		# so first I split it on "-" to get ["1", "3"]
		# then calling map on this iterable object means return a generator of calling int on everything in the second argument
		# so in this case it would return essentially [int("1"), int("3")] or [1,3]
		# since this will always be a list of 2 things, I unpack it into l(eft)h(and)s(ide) and rhs
		# so here lhs = 1, rhs = 3
		lhs,rhs = map(int,nums.split('-'))
		# here I abuse the fact that true casted to an int is 1, and false 0
		# if in the variable `pw` I count whatever letter I'm looking for the right number of times, then p1 increases by 1
		p1 += lhs <= pw.count(letter[0]) <= rhs
		# here I do a shitty XOR, by combining the strings together at the locations so in the example we do
		# "a"+"c" = "ac"
		# "ac".count("a") == 1, so only true if there is exactly one "a" in both spots
		p2 += (pw[lhs-1]+pw[rhs-1]).count(letter[0]) == 1
	return p1,p2