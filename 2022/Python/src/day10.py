from utils.aocUtils import *
def insert_newlines(string, every=64):
    return '\n'.join(string[i:i+every] for i in range(0, len(string), every))

cycle = 1
p2 = []

def main(input:str):
	p1 = 0
	X = 1
	check = 20
	p2 = []
	def updateCycle():
		global cycle
		p2.append('#' if abs(((cycle-1)%40)-X) <= 1 else ' ')
		cycle+=1

	for l in input.splitlines():
		if l.startswith("noop"):
			# Does nothing
			if cycle == check:
				p1 += X * check
				check += 40
			# End
			updateCycle()
		else:
			# addx
			# First round nothing happens
			if cycle == check:
				p1 += X * check
				check += 40
			updateCycle()
			# Second round finish 
			if cycle == check:
				p1 += X * check
				check += 40
			updateCycle()
			# Now add
			X += int(l.split()[1])
		if cycle >= 240:
			break
	p2 = "\n"+(insert_newlines("".join(p2), every=40))
	return (p1, p2)