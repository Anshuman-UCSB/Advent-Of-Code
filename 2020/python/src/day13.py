from utils.aocUtils import *
def p1s(input):
	nums = readNums(input)
	base = nums[0]
	out = 0
	while True:
		out+=1	
		for n in nums[1:]:
			if (base+out)%n == 0:
				return out*n
	
def p2s(input):
	n = []
	a = []
	for i, nm in enumerate(input.split(',')):
		if nm != 'x':
			n.append(int(nm))
			a.append(-i)
	print(n, a)
	return chinese_remainder(n, a)

def main(input:str):
	p1 = p1s(input)
	p2 = p2s(input.splitlines()[1])
	return (p1, p2)