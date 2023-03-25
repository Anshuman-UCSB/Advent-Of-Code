import re

"""
In state A:
  If the current value is 0:
    - Write the value 1.
    - Move one slot to the right.
    - Continue with state B.
  If the current value is 1:
    - Write the value 0.
    - Move one slot to the left.
    - Continue with state C.
"""
def parseState(state):
	spl = state.splitlines()
	v1 = int(spl[2][-2])
	d1 = 1 if spl[3][-3] == 'h' else -1
	n1 = ord(spl[4][-2])-ord("A")
	v2 = int(spl[6][-2])
	d2 = 1 if spl[7][-3] == 'h' else -1
	n2 = ord(spl[8][-2])-ord("A")
	return ((v1,d1,n1),(v2,d2,n2))

def day25(input):
	init,*states = input.split("\n\n")
	states = [parseState(st) for st in states]
	s = ord(init[15])-ord("A")
	steps = int(re.search(r"\d+",init).group(0))

	ticker = set()
	pos = 0
	for _ in range(steps):
		st = states[s]
		v,d,n=st[pos in ticker]
		if v:
			ticker|={pos}
		else:
			ticker-={pos}
		pos+=d
		s = n
		# print(st)
		# print(s,pos,ticker)

	return [len(ticker),None]