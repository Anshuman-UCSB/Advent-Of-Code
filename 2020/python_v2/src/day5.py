def parse(seat):
	row = int(seat[:7].replace('B','1').replace('F','0'),2)
	col = int(seat[7:].replace('R','1').replace('L','0'),2)
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