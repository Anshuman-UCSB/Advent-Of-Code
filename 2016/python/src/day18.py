def getRow(base):
	br = [True if c =='^' else False for c in base]
	br.append(False)
	br.insert(0, False)
	next = ""
	# ^^.
	# .^^
	# ^..
	# ..^
	for i in range(1, len(br)-1):
		next += "^" if br[i-1] != br[i+1] else "."
	return next
def main(input:str) -> tuple:
	p1 = 0
	p2 = 0
	for i in range(400000):
		if i<40:
			p1+=input.count('.')
		p2+=input.count('.')
		input = getRow(input)

	return (p1, p2)
