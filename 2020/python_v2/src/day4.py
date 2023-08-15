class passport:
	def __init__(self, inp):
		self.inp = inp.replace('\n',' ')
		self.properties = {}
		for p in self.inp.split():
			self.properties[p[:3]] = p[4:]
		self.has_all = all(x in self.properties for x in ("byr","iyr","eyr","hgt","hcl","ecl","pid"))
	def valid(self):
		if self.has_all == False:
			return False
		try:
			hgt = self.properties['hgt']
			return all((1920<=int(self.properties['byr'])<=2002,
						2010<=int(self.properties['iyr'])<=2020,
						2020<=int(self.properties['eyr'])<=2030,
						(hgt.endswith('cm') and 150<=int(hgt[:-2])<=193)
						 or (hgt.endswith('in') and 59<=int(hgt[:-2])<=76),
						self.properties['ecl'] in ("amb","blu","brn","gry","grn","hzl","oth"),
						self.properties['hcl'].startswith('#'),
						len(self.properties['hcl'][1:])==6,
						self.properties['hcl'][1:].isalnum(),
						len(self.properties['pid']) == 9,
						int(self.properties['pid'])>=0
						))
		except ValueError:
			return False
def main(input):
	p1 = 0
	p2 = 0
	for inp in input.split("\n\n"):
		pp = passport(inp)
		p1 += pp.has_all
		p2 += pp.valid()
	return p1,p2