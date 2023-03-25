import string

def get(a, regs):
	if a in string.ascii_lowercase:
		return regs[a]
	else:
		return int(a)

p1 = 0
def exec(instr, regs):
	global p1
	op,a,b = instr.split()
	# a=get(a,regs)
	# b=get(b,regs)
	if op == "set":
		regs[a]=get(b,regs)
	elif op == "sub":
		regs[a]-=get(b,regs)
	elif op == "mul":
		regs[a]*=get(b,regs)
		p1+=1
	elif op == "jnz":
		if get(a,regs):
			return get(b,regs)
	return 1

def day23(inp):
	regs = {k:0 for k in "abcdefgh"}
	p = 0
	instrs = inp.splitlines()
	while 0<=p<len(instrs):
		print(instrs[p],end="  \t")
		p+=exec(instrs[p],regs)
		for k,v in regs.items():
			print(f"{k}[{v}]",end='\t')
		input()

	# p2
	p = 0
	regs = {k:0 for k in "abcdefgh"}
	regs['a']=1
	while 0<=p<len(instrs):
		p+=exec(instrs[p],regs)
	return [p1,regs['h']]