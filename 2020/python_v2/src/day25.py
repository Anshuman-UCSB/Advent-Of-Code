def iter(n, sn):
	return (n*sn)%20201227
def main(input):
	card,door = map(int, input.splitlines())
	dn=None
	n = 1
	r = 0
	while not dn:
		r+=1
		n = iter(n,7)
		if dn == None and n == door:
			dn = r
	csn = card
	for it in range(dn-1):
		card =  iter(card,csn)
		# print(it, card)
	return card