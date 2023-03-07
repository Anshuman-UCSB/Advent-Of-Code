from string import ascii_lowercase
from collections import defaultdict,deque
pos=0
sound=None

class code:
	def __init__(self, id):
		self.regs = defaultdict(int,{"p":id})
		self.q=deque()
		self.pos=0
	def get(self,v):
		try: return int(v)
		except: return self.regs[v]
	def iter(self):
		 pass

def day18(inp):
	regs = defaultdict(int)
	def num(n):
		try:
			return int(n)
		except:
			return regs[n]
	def parse(cmd):
		global pos, sound
		op,*spl=cmd.split()
		if op=='snd':
			sound=num(spl[0])
			print("playing sound",sound)
		elif op=='set':
			regs[spl[0]]=num(spl[1])
		elif op=='add':
			regs[spl[0]]+=num(spl[1])
		elif op=='mul':
			regs[spl[0]]*=num(spl[1])
		elif op=='mod':
			regs[spl[0]]%=num(spl[1])
		elif op=='rcv':
			if num(spl[0]):
				return sound
		elif op=='jgz':
			if num(spl[0])>0:
				pos+=int(spl[1])-1
		pos+=1
	cmds=inp.splitlines()
	while 0<=pos<len(cmds):
		r = parse(cmds[pos])
		if r!=None:
			p1=r
			break
	return [p1,None]