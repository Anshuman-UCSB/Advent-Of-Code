from utils.aocUtils import *

def iter(doubles, pairs):
	n = Counter()
	for k, v in doubles.items():
		if k in pairs:
			n[k[0]+pairs[k]]+=v
			n[pairs[k]+k[1]]+=v
		else:
			print(n, k)
			print(k)
			n[k]+=v
	return n

def score(doubles, base):
	c = Counter([base[0], base[-1]])
	for k, v in doubles.items():
		for l in k:
			c[l]+=v
	cmn = c.most_common()
	return (cmn[0][1]-cmn[-1][1])//2
	

def main(input:str):
	p1 = 0
	pairs = {}
	base = input.splitlines()[0]
	doubles = Counter([base[i:i+2] for i in range(len(base)-1)])
	for l in input.splitlines()[2:]:
		spl = l.split()
		pairs[spl[0]] = spl[2]
	for r in range(40):
		if r == 10:
			p1 = score(doubles, base)
		doubles = iter(doubles, pairs)
	return (p1, score(doubles, base))