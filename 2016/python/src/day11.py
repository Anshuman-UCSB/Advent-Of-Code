import re
from collections import deque
from time import sleep
from copy import deepcopy, copy
from itertools import combinations, chain

cache = set()
class State:
	def __init__(self, startFloor, step = 0):
		self.generators = {}
		self.chips = {}
		self.elevator = startFloor
		self.step = step

	def isValid(self):
		checkFloors = set()
		for f in self.generators.values():
			checkFloors.add(f)
		for c, f in [(c,k) for c,k in self.chips.items() if k in checkFloors]:
			if self.generators[c] != f:
				return False
		return True

	def pushNextStates(self, q):
		pool = []
		for chip, floor in self.chips.items():
			if(floor == self.elevator):
				pool.append((False,chip))
		for gen, floor in self.generators.items():
			if(floor == self.elevator):
				pool.append((True, gen))
		for x in chain(combinations(pool, 2),combinations(pool, 1)):
			if(self.elevator>0):
				s = State(self.elevator-1, self.step +1)
				s.generators = copy(self.generators)
				s.chips = copy(self.chips)
				for val in x:
					(s.generators if val[0] else s.chips)[val[1]]-=1
				if s.isValid():
					q.append(s)
				# else:
				# 	print(s.hash(), "is invalid.")
			if(self.elevator<3):
				s = State(self.elevator+1, self.step +1)
				s.generators = copy(self.generators)
				s.chips = copy(self.chips)
				for val in x:
					(s.generators if val[0] else s.chips)[val[1]]+=1
				if s.isValid():
					q.append(s)
				# else:
				# 	print(s.hash(), "is invalid.")

	def hash(self):
		return str(self.elevator)+str(self.chips)+str(self.generators)

	def done(self):
		for k in list(self.generators.values()) + list(self.chips.values()):
			if k!=3:
				return False
		return True

def main(input:str) -> tuple:
	state = State([])
	q = deque()
	for fn, l in enumerate(input.splitlines()):
		for g in re.findall(r"(\w+) generator", l):
			state.generators[g] = fn
		for c in re.findall(r"(\w+)-", l):
			state.chips[c] = fn
		state.elevator = 0
	q.append(state)
	p1 = 0
	while(len(q)>0):
		t = q.popleft()
		assert(t.isValid())
		if t.hash() not in cache:
			cache.add(t.hash())
			if t.done():
				p1 = t.step
				break
			t.pushNextStates(q)
	state.chips["elerium"] = 0
	state.chips["dilithium"] = 0
	state.generators["elerium"] = 0
	state.generators["dilithium"] = 0
	q = deque()
	q.append(state)
	cache.clear()
	p2 = 0
	while(len(q)>0):
		t = q.popleft()
		assert(t.isValid())
		if t.hash() not in cache:
			cache.add(t.hash())
			if t.done():
				p2 = t.step
				break
			t.pushNextStates(q)
	return (p1, p2)
