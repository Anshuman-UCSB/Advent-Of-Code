def main(input:str) -> tuple:
	p2, f = 0, 1
	for p2, c in enumerate(input):
		f+= 1 if c=='(' else -1
		if not f: break
	return (input.count('(')-input.count(')'), p2+1)