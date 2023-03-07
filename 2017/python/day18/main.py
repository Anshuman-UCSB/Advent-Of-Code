from string import ascii_lowercase
from collections import defaultdict,deque
pos=0
sound=None
cmds=[]
class code:
	def __init__(self, id):
		self.regs = defaultdict(int,{"p":id})
		self.q=deque()
		self.pos=0
		self.outq=None
		self.stuck=False
	def setOther(self,other):
		self.outq=other.q
		other.outq=self.q
	def get(self,v):
		try: return int(v)
		except: return self.regs[v]
	def iter(self):
		self.stuck=False
		op,*spl = cmds[self.pos].split()
		if op=='snd':
			self.outq.append(num(spl[0]))
		elif op=='set':
			self.regs[spl[0]]=num(spl[1])
		elif op=='add':
			self.regs[spl[0]]+=num(spl[1])
		elif op=='mul':
			self.regs[spl[0]]*=num(spl[1])
		elif op=='mod':
			self.regs[spl[0]]%=num(spl[1])
		elif op=='rcv':
			if self.q:
				self.regs[spl[0]]=self.q.popleft()
			else:
				self.stuck=True
				pos-=1
		elif op=='jgz':
			if num(spl[0])>0:
				self.pos+=int(spl[1])-1
		self.pos+=1

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
			# print("playing sound",sound)
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
	cmds.extend(inp.splitlines())
	while 0<=pos<len(cmds):
		r = parse(cmds[pos])
		if r!=None:
			p1=r
			break
	A,B=code(0),code(1)
	A.setOther(B)
	return [p1,None]