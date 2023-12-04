def matches(l):
	_, l = l.split(":")
	lhs, rhs = l.split("|")
	return len(set(lhs.split()) & set(rhs.split()))

def main(input):
	p1 = 0
	cards = [1]*len(input.splitlines())
	for c,l in enumerate(input.splitlines()):
		num_matches = matches(l)
		p1 += int(2**(num_matches-1))
		for i in range(num_matches):
			cards[c+i+1] += cards[c]
	return p1, sum(cards)