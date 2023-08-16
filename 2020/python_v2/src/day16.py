class Field:
	def __init__(self, line):
		self.name, line = line.split(":")
		
		self.ranges = [tuple(map(int, r.split('-'))) for r in line.split()[::2]]
	def inRange(self, num):
		return any(r[0]<=num<=r[1] for r in self.ranges)
	def __repr__(self):
		return self.name

def validNum(fields, num):
	return any(f.inRange(num) for f in fields)
		
def main(input):
	definitions, mine, nearby = input.split('\n\n')
	fields = [Field(l) for l in definitions.splitlines()]
	mine = tuple(map(int, mine.splitlines()[1].split(",")))
	tickets = [tuple(map(int, l.split(","))) for l in nearby.splitlines()[1:]]
	valids = []
	p1 = 0
	for t in tickets:
		good = True
		for v in t:
			if validNum(fields, v) == False:
				p1+=v
				good = False
		if good:
			valids.append(t)
	possibles = [set(fields) for _ in fields]
	for t in valids:
		for i,n in enumerate(t):
			possibles[i] = {f for f in possibles[i] if f.inRange(n)}
	locked = set()
	p2 = 1
	while len(locked) < len(fields):
		for i,s in enumerate(possibles):
			s -= locked
			if len(s) == 1:
				locked|=s
				name,=s
				if "departure" in name.name:
					p2 *= mine[i]
	return p1, p2