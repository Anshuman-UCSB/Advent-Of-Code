from string import ascii_lowercase
pos=0
def day18(input):
	regs = {l:0 for l in ascii_lowercase}
	def num(n):
		try:
			return int(n)
		except:
			return regs[n]
	def parse(cmd):
		global pos
		op,*spl=cmd.split()
		if op=='snd':
			pass
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
				pass # recover?
		elif op=='jgz':
			if num(spl[0])>0:
				pos+=int(spl[1])-1
		pos+=1
	cmds=input.splitlines()
	while 0<=pos<len(cmds):
		parse(cmds[pos])
		print(pos)
	print(regs)
	return [None,None]