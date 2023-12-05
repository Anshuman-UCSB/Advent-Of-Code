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

def p2(seeds, maps):
	ranges = []
	for i in range(0,len(seeds),2):
		ranges.append(Range(seeds[i], seeds[i]+seeds[i+1]))
	for m in maps:
		new_ranges = []
		while ranges:
			r = ranges.pop(-1)
			for dest, source, size in m.rules:
				m_range = Range(source, source+size)
				ins = r.intersection(m_range)
				if ins is not None:
					new_ranges.append(Range(ins.lower+dest-source,ins.upper+dest-source))
					sub = r.subtract(ins)
					if sub == []:
						r = None
						break
					if len(sub)==2:
						ranges.append(sub[1])
						r = sub[0]
			if r is not None:
				new_ranges.append(r)
		ranges = new_ranges
	print(ranges)
	return min([r.lower for r in ranges])


def solve(seeds, maps):
	locations = [getLocation(s, maps) for s in seeds]
	return min(locations)

def main(input):
	seeds, *maps = input.split("\n\n")
	seeds = list(map(int, seeds.split()[1:]))
	maps = list(map(Map, maps))

	return solve(seeds, maps), p2(seeds, maps)