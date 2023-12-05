# P2 inspired by /u/Wayoshi

class Range:
	def __init__(self, lower, upper):
		self.lower = lower
		self.upper = upper
	def intersection(self, other):
		tmp = Range(max(self.lower, other.lower), min(self.upper, other.upper))
		return tmp if tmp.lower < tmp.upper else None
	def subtract(self, other):
		ins = self.intersection(other)
		if ins == None:	# No intersection, so no change
			return [Range(self.lower, self.upper)]
		elif (ins.lower, ins.upper) == (self.lower, self.upper):
			#    -----		intersect
			#    -----		self
			return []
		elif ins.lower == self.lower:
			#    --			intersect
			#    -----		self
			return [Range(ins.upper, self.upper)]
		elif ins.upper == self.upper:
			#       --		intersect
			#    -----		self
			return [Range(self.lower, ins.lower)]
		else:
			#      --		intersect
			#    -----		self
			return [Range(self.lower, ins.lower), Range(ins.upper, self.upper)]
	def add(self, offset):
		return Range(self.lower+offset, self.upper+offset)
	def __repr__(self):
		return f"[{self.lower}, {self.upper})"

class Map:
	def __init__(self, map_str):
		self.rules = []
		for l in map_str.splitlines()[1:]:
			dest, source, size = map(int, l.split())
			self.rules.append((dest, source, size))
	def convert(self, inp):
		for dest, source, size in self.rules:
			if source<=inp<source+size:
				return dest + inp - source
		return inp

def getLocation(seed, maps):
	for m in maps:
		seed = m.convert(seed)
	return seed

class p2solver:
	def __init__(self, maps):
		self.final_ranges = []
		self.answer = float('inf')
		self.maps = maps
	def propogate(self, r: Range, layer: int):
		if layer == len(self.maps):
			self.final_ranges.append(r)
			self.answer = min(self.answer, r.lower)
			return
		for dest, source, size in self.maps[layer].rules:
			map_r = Range(source, source+size)
			ins = r.intersection(map_r)
			if ins is not None:
				self.propogate(ins.add(dest-source), layer+1)
				sub = r.subtract(ins)
				if len(sub) == 0:
					return
				r = sub[0]
				if len(sub) == 2:
					self.propogate(sub[1], layer)
		self.propogate(r, layer+1)

def solve(seeds, maps):
	locations = [getLocation(s, maps) for s in seeds]
	return min(locations)

def main(input):
	seeds, *maps = input.split("\n\n")
	seeds = list(map(int, seeds.split()[1:]))
	maps = list(map(Map, maps))
	p2 = p2solver(maps)
	for i in range(0,len(seeds),2):
		p2.propogate(Range(seeds[i], seeds[i]+seeds[i+1]), 0)

	return solve(seeds, maps), p2.answer