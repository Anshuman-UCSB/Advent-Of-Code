from utils.aocUtils import *
from itertools import zip_longest
from copy import deepcopy
from heapq import *

def getRoom(letter):
	match letter:
		case 'A': return 2
		case 'B': return 4
		case 'C': return 6
		case 'D': return 8
def getMoves(state, room, pos):
	letter = state[room][pos]
	if letter == 'E':
		return set()
	visitable = []
	for rng in [range(room, -1, -1), range(room+1, len(state))]:
		for p in rng:
			if p not in [2,4,6,8] and state[p][0]!='E':
				break
			visitable.append(p)
	visitable.sort()
	
	trg = getRoom(letter)
	if trg == room and pos == 1:
		return set() #already big chillin
	if trg in visitable:
		if state[trg][0] == 'E':
			if state[trg][1] == 'E':
				return set([(trg, 1)])
			if state[trg][1] == letter:
				return set([(trg, 0)])
	if room not in [2,4,6,8]: #in corridor, and couldn't go to target room, no moves
		return set()
	
	return set((v,0) for v in visitable if v not in [2,4,6,8])

@cache
def getCost(letter, rs, ps, re, pe):
	cost = 0
	if rs in [2,4,6,8]:
		cost+=ps+1 #if pos 0, need to take one step to get to top
	if re in [2,4,6,8]:
		cost+=pe+1 #if pos 0, need to take one step to get to top
	cost+=abs(rs - re)
	return cost * 10**(ord(letter)-ord('A'))
	
def isSolved(state):
	return str(state) == "[['E'], ['E'], ['A', 'A'], ['E'], ['B', 'B'], ['E'], ['C', 'C'], ['E'], ['D', 'D'], ['E'], ['E']]"
		
def pprint(st):
	c = [[x if x != 'E' else '.' for x in r] for r in st]
	for x in [2,4,6,8]:
		c[x].insert(0,'.')
	for r in (zip_longest(*c, fillvalue=" ")):
		print("".join(r))
	
def main(inp:str):
	p1 = p2 = 0
	matches = re.findall(r"[A-Z]", inp)
	state = [matches[i::4] for i in range(4)]
	state = [['E'], ['E'], state[0], ['E'], state[1], ['E'], state[2], ['E'], state[3], ['E'], ['E']]
	# print(getMoves(state, 1,0))
	q = [(0, state)]
	seen = set()
	while len(q):
		cost, st = heappop(q)
		# if random()<.001:
		if str(st) in seen:
			continue
		if isSolved(st):
			p1 = cost
			break
		# input()
		seen.add(str(st))
		for r in range(len(st)):
			pos = 0
			if r in [2,4,6,8] and st[r][0] == 'E':
				pos+=1
			for m in getMoves(st, r, pos):
				if cost == 12513:
					print(cost)
					pprint(st)
				ns = [r[:] for r in st]
				ns[r][pos], ns[m[0]][m[1]]=ns[m[0]][m[1]], ns[r][pos]
				heappush(q, (cost+getCost(st[r][pos], r, pos, m[0], m[1]), ns))
	
	return (p1, p2)