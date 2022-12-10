from utils.aocUtils import *

def main(input:str):
	nodes = [0 for _ in range(10)]
	translation = {"U":1j, "R":1, "D":-1j, "L":-1}
	update = {}
	for i in range(-1,2):
		for k in range(-1,2):
			update[i+k*1j]=0
	update[2+2j] 	= update[1+2j] 	= update[2+1j] 	= 1+1j
	update[2-2j] 	= update[1-2j] 	= update[2-1j] 	= 1-1j
	update[-2+2j] 	= update[-1+2j] = update[-2+1j] = -1+1j
	update[-2-2j] 	= update[-1-2j] = update[-2-1j] = -1-1j
	update[-2] 	= -1
	update[2] 	= 1
	update[-2j] = -1j
	update[2j] 	= 1j

	p1 = set()
	p2 = set()

	for l in input.splitlines():
		spl = l.split()
		dir, count = spl[0], int(spl[1])
		for _ in range(count):
			nodes[0]+=translation[dir]
			for i in range(9):
				nodes[i+1] += update[nodes[i]-nodes[i+1]]
				p1.add(nodes[1])
				p2.add(nodes[9])
	
	return (len(p1), len(p2))