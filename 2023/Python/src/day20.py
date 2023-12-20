class Module:
	def __init__(self, line):
		name, dests = line.split(" -> ")
		if name == "broadcaster":
			self.name = name
			self.type = 'B'
		else:
			self.name = name[1:]
			self.type = name[0]
		self.state = False
		self.dests = dests.split(", ")
		self.inputs = {}
	def __repr__(self):
		return self.type+" "+self.name+"->"+str(self.dests)+'\t'+str(self.inputs)

class System:
	def __init__(self, input):
		self.modules = {m.name:m for m in map(Module, input.splitlines())}
		for empty in ("rx", "output"):
			self.modules[empty] = Module(empty+" -> ")
			self.modules[empty].dests = []
		for m in self.modules.values():
			for d in m.dests:
				self.modules[d].inputs[m.name] = False
		try:
			self.parent = min(self.modules['rx'].inputs.keys())
			self.listen = {n:None for n in self.modules[self.parent].inputs.keys()}
			print(self.listen)
		except ValueError:
			# Test case
			self.parent = None
			self.listen = {}
		self.Q = []
		self.pulses = [0,0]
		self.buttonPresses = 0
	def buttonPress(self):
		self.buttonPresses += 1
		assert self.Q == []
		self.Q = [("button","broadcaster",False)]
		while self.Q:
			self.process(*self.Q.pop(0))
	def score(self):
		return self.pulses[0]*self.pulses[1]
	def score2(self):
		ans = 1
		for v in self.listen.values():
			ans*=v
		return ans
	def process(self, source, name, level):
		self.pulses[level]+=1
		mod = self.modules[name]
		if mod.type == '%':
			if level: return
			mod.state = not mod.state
		elif mod.type == '&':
			mod.inputs[source] = level
			mod.state = not all(mod.inputs.values())
			if name == self.parent:
				for k,v in self.listen.items():
					if v is None and k == source and level:
						self.listen[k] = self.buttonPresses # + 1
		for d in mod.dests:
			self.Q.append((name, d, mod.state))
	def __repr__(self):
		return str(self.modules)

def main(input):
	s = System(input)
	for _ in range(1000):
		s.buttonPress()
	p1 = s.score()
	while None in s.listen.values():
		s.buttonPress()
	return p1, s.score2()