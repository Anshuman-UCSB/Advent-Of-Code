from src.aocUtils import readNums

bots = {}
outputs = {}
p1 = None
class bot:
	def __init__(self, a, b):
		self.chips = []
		self.targets = [a, b]
		
	def add(self, value):
		assert(len(self.chips)<2)
		self.chips.append(value)
		self.chips.sort()
		if(len(self.chips) == 2):
			if(self.chips == [17,61]):
				global p1
				p1 = [b for b,v in bots.items() if v == self][0]
			for b, v in zip(self.targets, self.chips):
				if(b<0):
					outputs[-(b+1)] = v
				else:
					bots[b].add(v)


def main(input:str) -> tuple:
	instrs = []
	for l in input.splitlines():
		instr = readNums(l)
		if(len(instr) == 3):
			a, b = instr[1:]
			spl = l.split()
			if(spl[5] == 'output'):
				a = -a-1
			if(spl[10] == 'output'):
				b = -b-1

			bots[instr[0]] = bot(a,b)
		else:
			instrs.append(instr)

	for ins in instrs:
		bots[ins[1]].add(ins[0])
	return (p1, outputs[0]*outputs[1]*outputs[2])