def parse(seat):
	row = int("".join(['1' if l == 'B' else '0' for l in seat[:7]]),2)
	col = int("".join(['1' if l == 'R' else '0' for l in seat[7:]]),2)
	return row*8+col	
	
def main(input):
	p1 = 0
	possible = set()
	seen = set()
	for l in input.splitlines():
		sid = parse(l)
		p1 = max(p1, sid)
		possible.add(sid+1)
		possible.add(sid-1)
		seen.add(sid)
	possible -= seen
	return p1, sorted(possible)[1]