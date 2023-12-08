import re
from math import lcm

def loop(instr):
	instr = [0 if ins == 'L' else 1 for ins in instr]
	while True:
		yield from instr

def solve(instr, net, pos):
	ans = 0
	if pos not in net:
		return "ERROR"
	for i in loop(instr):
		if pos[-1] == 'Z': break
		ans += 1
		pos = net[pos][i]
	return ans

def main(input):
	instr, nodes = input.split("\n\n")
	net = {}
	for l in nodes.splitlines():
		source, left, right = re.findall(r"[0-9A-Z]+", l)
		net[source] = (left, right)
	
	periods = []
	for n in filter(lambda x: x[-1] == 'A', net):
		periods.append(solve(instr, net, n))
	print(periods)

	return solve(instr, net, "AAA"), lcm(*periods)