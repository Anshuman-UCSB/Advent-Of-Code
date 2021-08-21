import re
from collections import defaultdict

def main(input:str) -> tuple:
	p1 = 0
	p2 = None
	for l in input.splitlines():
		spl = re.split("-|\[|\]", l)
		counter = defaultdict(int)
		for s in spl[:-3]:
			for c in s:
				counter[c]+=1

		if spl[-2] ==  "".join([x[0] for x in sorted(counter.items(), key =lambda x: (-x[1],x[0]))[:5]]):
			p1+=int(spl[-3])
			build = ""
			for x in spl[:-3]:
				for c in x:
					build+=chr((ord(c)-ord('a')+int(spl[-3]))%26+ord('a'))
			if(p2 == None and build == "northpoleobjectstorage"):
				p2 = int(spl[-3])

	return (p1, p2)
