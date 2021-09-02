from utils.aocUtils import *

def p1(input):
	cups = [int(c) for c in list(input)]
	size = len(cups)
	m = {}
	for i in range(len(cups)-1, -1, -1):
		m[cups[i-1]]=cups[i]
	cur = cups[0]
	for _ in range(100):
		rem = [m[cur], m[m[cur]], m[m[m[cur]]]]
		m[cur] = m[rem[-1]]
		target = (cur-2)%size+1
		while target in rem:
			target = (target-2)%size+1
		targetN = m[target]
		m[target] = rem[0]
		m[rem[-1]] = targetN
		cur = m[cur]
	t = m[1]
	out = ""
	for _ in range(size-1):
		out+=str(t)
		t = m[t]
	return out

def p2Brute(input):
	cups = [int(c) for c in list(input)]
	while len(cups)<1000000:
		cups.append(len(cups)+1)
	size = len(cups)
	m = {}
	for i in range(len(cups)-1, -1, -1):
		m[cups[i-1]]=cups[i]
	cur = cups[0]
	for _ in range(10000000):
		rem = [m[cur], m[m[cur]], m[m[m[cur]]]]
		m[cur] = m[rem[-1]]
		target = (cur-2)%size+1
		while target in rem:
			target = (target-2)%size+1
		targetN = m[target]
		m[target] = rem[0]
		m[rem[-1]] = targetN
		cur = m[cur]
	return m[1]*m[m[1]]
	


def main(input:str):
	return (p1(input), p2Brute(input))