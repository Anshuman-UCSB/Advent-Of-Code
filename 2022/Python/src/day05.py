from utils.aocUtils import *
from copy import deepcopy

def main(input:str):
	stacks = [[] for _ in range(9)]
	inp_part = 0
	
	for l in input.splitlines():
		if l == "":
			continue
		if l.startswith(" 1   2 "):
			inp_part = 1
			for i in range(len(stacks)):
				stacks[i] = stacks[i][::-1]
			stacks2 = deepcopy(stacks)
		elif inp_part == 0:
			try:
				for i in range(9):
					if l[1+i*4]!=' ':
						stacks[i].append(l[1+i*4])
			except IndexError:
				continue
		elif inp_part == 1:
			spl = l.split()
			cnt, a, b = int(spl[1]), int(spl[3])-1, int(spl[5])-1
			tmp = []
			for _ in range(cnt):
				stacks[b].append(stacks[a].pop(-1))
				tmp.insert(0, stacks2[a].pop(-1))
			stacks2[b]+=tmp
	p1 = ""
	for s in stacks:
		if s:
			p1+=s.pop(-1)
	p2 = ""
	for s in stacks2:
		if s:
			p2+=s.pop(-1)
	return (p1, p2)