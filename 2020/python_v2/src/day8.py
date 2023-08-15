def simulate(instrs):
	acc = 0
	pos = 0
	visited = set()
	while 0<=pos<len(instrs):
		if pos in visited: break
		visited |= {pos}
		if instrs[pos][:3] == "acc":
			acc += int(instrs[pos][4:])
		elif instrs[pos][:3] == "jmp":
			pos += int(instrs[pos][4:]) - 1
		pos+=1
	return acc, pos==len(instrs)

def main(input):
	instrs = input.splitlines()
	p1 = simulate(instrs)[0]
	i = -1
	while i<=len(instrs):
		i+=1
		if instrs[i][:3] == "acc":continue
		elif instrs[i][:3] == "nop":
			instrs[i] = instrs[i].replace("nop", "jmp")
			acc, halt = simulate(instrs)
			if halt:
				return p1, acc
			instrs[i] = instrs[i].replace("jmp", "nop")
		elif instrs[i][:3] == "jmp":
			instrs[i] = instrs[i].replace("jmp", "nop")
			acc, halt = simulate(instrs)
			if halt:
				return p1, acc
			instrs[i] = instrs[i].replace("nop", "jmp")
	return p1, None