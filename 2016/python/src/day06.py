from collections import defaultdict

def main(input:str) -> tuple:
	spl = input.splitlines()
	counters = [defaultdict(int) for _ in range(len(spl[0]))]
	for l in spl:
		for i in range(len(l)):
			counters[i][l[i]]+=1
	p1 = ""
	p2 = ""
	for c in counters:
		p1+=max(c, key=lambda x:c[x])
		p2+=min(c, key=lambda x:c[x])
	return (p1, p2)
