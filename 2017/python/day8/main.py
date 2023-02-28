from collections import defaultdict
import operator
p2=0
def day8(input):
	regs = defaultdict(int)
	ops = {
		">":operator.gt,
		">=":operator.ge,
		"<":operator.lt,
		"<=":operator.le,
		"==":operator.eq,
		"!=":operator.ne,
	}
	def evalLine(l):
		global p2
		t,d,c1,_if,comp,op,c2=l.split()
		c1,c2=map(int,(c1,c2))
		if ops[op](regs[comp],c2):
			regs[t]+=c1 if d[0]=='i' else -c1
			p2=max(p2,regs[t])
	for l in input.splitlines():
		evalLine(l)
	
	return [max(regs.values()),p2]