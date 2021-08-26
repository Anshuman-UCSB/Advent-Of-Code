from utils.aocUtils import readNums

class deer:
	def __init__(self, line):
		self.name = line.split()[0]
		self.speed, self.dur, self.rest=readNums(line)
		self.period = self.dur + self.rest

def p1(deers):
	pos = {d.name:0 for d in deers}
	for t in range(2503):
		for d in deers:
			if t%d.period <d.dur:
				pos[d.name]+=d.speed
	return max(pos.values())
def p2(deers):
	pos = {d.name:0 for d in deers}
	scores = {d.name:0 for d in deers}
	for t in range(2503):
		mxDist = 0
		for d in deers:
			if t%d.period <d.dur:
				pos[d.name]+=d.speed
			mxDist = max(mxDist, pos[d.name])
		for name, dist in pos.items():
			if dist == mxDist:
				scores[name]+=1
	return max(scores.values())

def main(input:str) -> tuple:
	deers = [deer(l) for l in input.splitlines()]
	return (p1(deers),p2(deers))