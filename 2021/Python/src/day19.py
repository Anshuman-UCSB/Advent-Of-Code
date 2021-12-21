from utils.aocUtils import *
from itertools import permutations, combinations, product

def rot(coords):
	a, b, c = coords

	yield (+a, +b, +c);yield (+b, +c, +a);yield (+c, +a, +b)
	yield (+c, +b, -a);yield (+b, +a, -c);yield (+a, +c, -b)
	yield (+a, -b, -c);yield (+b, -c, -a);yield (+c, -a, -b)
	yield (+c, -b, +a);yield (+b, -a, +c);yield (+a, -c, +b)
	yield (-a, +b, -c);yield (-b, +c, -a);yield (-c, +a, -b)
	yield (-c, +b, +a);yield (-b, +a, +c);yield (-a, +c, +b)
	yield (-a, -b, +c);yield (-b, -c, +a);yield (-c, -a, +b)
	yield (-c, -b, -a);yield (-b, -a, -c);yield (-a, -c, -b)

def hash(a, b):
	out=str(dist(a,b))
	out+=","
	out+=str(min(abs(x-y) for x,y in zip(a,b)))
	out+=","
	out+=str(max(abs(x-y) for x,y in zip(a,b)))
	return out

class Scanner:
	def __init__(self, inp):
		self.id = readNums(inp.splitlines()[0])[0]
		self.beacons = [tuple(readNums(l)) for l in inp.splitlines()[1:]]
		self.hashes = [hash(a,b) for a,b in permutations(self.beacons, 2)]

def main(input:str):
	p2 = 0
	knownPos = {0:(0,0,0)} #scanner 0 known
	scanners = [Scanner(x) for x in input.split("\n\n")]
	while len(knownPos) < len(scanners):
		for a,b in combinations(scanners,2):
			if (len(set(a.hashes)&set(b.hashes)) == 66): #12 choose 2
				if((a.id in knownPos) != (b.id in knownPos)):
					if b.id in knownPos:
						a,b = b,a
					t = list(zip(*[list(rot(p)) for p in b.beacons]))
					for rotset in t:
						c = Counter()
						for p in rotset:
							c+=Counter([sub(n,p) for n in a.beacons])
							ans = [k for k,v in c.items() if v>=12]
							if len(ans):
								knownPos[b.id]=add([k for k,v in c.items() if v>=12][0], knownPos[a.id])
								b.beacons = rotset
								break
						if b.id in knownPos:
							break
	p1 = set()
	for sn in scanners:
		for p in sn.beacons:
			p1.add(add(p, knownPos[sn.id]))
	for a in knownPos.values():
		for b in knownPos.values():
			p2 = max(p2, manhattan(a,b))
	return (len(p1), p2)