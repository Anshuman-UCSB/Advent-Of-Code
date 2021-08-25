from itertools import groupby

def iter(base):
	return "".join("{}{}".format(b, a) for a, b in [(l, len(list(gr))) for l, gr in groupby(base)])

def main(input:str) -> tuple:
	for i in range(40):
		input = iter(input)
	p1 = len(input)
	for i in range(10):
		input = iter(input)
	return (p1, len(input))