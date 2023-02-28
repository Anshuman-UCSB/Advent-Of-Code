# Run with pypy
def day5(input):
	def sim(input):
		regs = list(map(int,input.splitlines()))
		i = 0
		steps=0
		while 0<=i<len(regs):
			steps+=1
			regs[i]+=1
			i+=regs[i]-1
		return steps
	def sim2(input):
		regs = list(map(int,input.splitlines()))
		i = 0
		steps=0
		while 0<=i<len(regs):
			v = regs[i]
			steps+=1
			regs[i]+=-1 if v>=3 else 1
			i+=v
		return steps

	return [sim(input),sim2(input)]