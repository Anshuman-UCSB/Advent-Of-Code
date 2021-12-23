from utils.aocUtils import *
from heapq import *

def getRoom(letter):
	match letter:
		case 'A': return 2
		case 'B': return 4
		case 'C': return 6
		case 'D': return 8
def getMoves(state, room, pos, part1=True):
	letter = state[room][pos]
	if letter == 'E':
		return set()
	visitable = [room]
	for rng in [range(room-1, -1, -1), range(room+1, len(state))]:
		for p in rng:
			if p not in [2,4,6,8] and state[p][0]!='E':
				break
			visitable.append(p)
	visitable.sort()
	
	trg = getRoom(letter)
	if trg == room and pos == len(state[trg])-1:
		return set()
	deepest = -1
	if trg in visitable:
		for r in range(len(state[trg])-1,-1,-1):
			if state[trg][r] == 'E':
				deepest = max(deepest, r)
			elif state[trg][r] != letter:
				break
		else:
			if deepest != -1:
				return set([(trg, deepest)])
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
	return str(state) == "[['E'], ['E'], ['A', 'A'], ['E'], ['B', 'B'], ['E'], ['C', 'C'], ['E'], ['D', 'D'], ['E'], ['E']]" or \
		   str(state) == "[['E'], ['E'], ['A', 'A', 'A', 'A'], ['E'], ['B', 'B', 'B', 'B'], ['E'], ['C', 'C', 'C', 'C'], ['E'], ['D', 'D', 'D', 'D'], ['E'], ['E']]"
	
def solve(inp):
	matches = re.findall(r"[A-Z]", inp)
	state = [matches[i::4] for i in range(4)]
	state = [['E'], ['E'], state[0], ['E'], state[1], ['E'], state[2], ['E'], state[3], ['E'], ['E']]
	q = [(0, state)]
	seen = set()
	while len(q):
		cost, st = heappop(q)
		if str(st) in seen:
			continue
		if isSolved(st):
			return cost
		seen.add(str(st))
		for r in range(len(st)):
			pos = 0
			while r in [2,4,6,8] and pos<len(st[r])-1 and st[r][pos] == 'E':
				pos+=1
			for m in getMoves(st, r, pos, False):
				ns = [r[:] for r in st]
				ns[r][pos], ns[m[0]][m[1]]=ns[m[0]][m[1]], ns[r][pos]
				heappush(q, (cost+getCost(st[r][pos], r, pos, m[0], m[1]), ns))

def main(inp:str):
	p1 = solve(inp)
	inp = inp.splitlines()
	inp.insert(3, "  #D#C#B#A#")
	inp.insert(4, "  #D#B#A#C#")
	p2 = solve("\n".join(inp))
	return (p1, p2)