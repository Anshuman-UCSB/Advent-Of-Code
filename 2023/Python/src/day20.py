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
		self.modules['rx'] = Module("rx -> ")
		self.modules['rx'].dests = []
		for m in self.modules.values():
			for d in m.dests:
				self.modules[d].inputs[m.name] = False
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
	def process(self, source, name, level):
		self.pulses[level]+=1
		mod = self.modules[name]
		# print(f"{source} -{'high' if level else 'low'}-> {name}")
		if mod.type == '%':
			if level: return
			mod.state = not mod.state
		elif mod.type == '&':
			mod.inputs[source] = level
			mod.state = not all(mod.inputs.values())
		for d in mod.dests:
			self.Q.append((name, d, mod.state))
	def __repr__(self):
		return str(self.modules)

def main(input):
	s = System(input)
	parent = min(s.modules['rx'].inputs.keys())
	listeners = {n:None for n in s.modules[parent].inputs.keys()}
	while None in listeners.values():
		s.buttonPress()
		if s.buttonPresses == 1000:
			p1 = s.score()
			break
	return p1, None