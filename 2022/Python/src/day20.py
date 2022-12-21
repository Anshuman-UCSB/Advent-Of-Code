from utils.aocUtils import *

def main(input:str):
	p1 = p2 = 0
	inp1 = [*enumerate(int(x) * 1 for x in input.splitlines())]
	inp2 = [*enumerate(int(x) * 811589153 for x in input.splitlines())]
	for x in inp1 * 1:
		inp1.pop(i := inp1.index(x))
		inp1.insert((i+x[1]) % len(inp1), x)
	inp1 = [x for _,x in inp1]
	zind = inp1.index(0)
	for di in (1000,2000,3000):
		p1+=inp1[(zind+di)%len(inp1)]


	for x in inp2 * 10:
		inp2.pop(i := inp2.index(x))
		inp2.insert((i+x[1]) % len(inp2), x)
	inp2 = [x for _,x in inp2]
	zind = inp2.index(0)
	for di in (1000,2000,3000):
		p2+=inp2[(zind+di)%len(inp2)]

	return (p1, p2)