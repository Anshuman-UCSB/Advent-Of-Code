from utils.aocUtils import *
def eval(inp, dx):
	out = 0
	# print()
	for i, v in enumerate(inp.splitlines()):
		# print((i*dx)%len(v), i)
		if v[(i*dx)%len(v)] == '#':
			out+=1
	return out
def slope2(inp):
	out = 0
	for i, v in enumerate(inp.splitlines()):
		if i%2==0 and v[int(i/2)%len(v)] == '#':
			out+=1
	return out

def main(input:str):
	print([eval(input, x) for x in [1,3,5,7]])
	print(slope2(input))
	return (eval(input, 3), prod([eval(input, x) for x in [1,3,5,7]])*slope2(input))