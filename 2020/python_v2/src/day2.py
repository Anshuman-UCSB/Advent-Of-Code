def main(input):
	p1 = 0
	p2 = 0
	for l in input.splitlines():
		nums,letter,pw = l.split(' ')
		lhs,rhs = map(int,nums.split('-'))
		p1 += lhs<=pw.count(letter[0])<=rhs
		p2 += (pw[lhs-1]+pw[rhs-1]).count(letter[0]) == 1
	return p1,p2