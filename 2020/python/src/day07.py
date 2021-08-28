from utils.aocUtils import *
from collections import defaultdict
import re

def recurseSum(bags, name):
	if bags[name] == []:
		return 1
	else:
		return sum([recurseSum(bags, x)*c for x,c in bags[name]])+1
	
def main(input:str):
	bags = defaultdict(list)
	for l in input.splitlines():
		bag_name = " ".join(l.split()[:2])
		m = re.findall(r"(\d+) (\w+ \w+)", l)
		bags[bag_name] = [(bag, int(count)) for count, bag in m]
	holdGold = set(["shiny gold"])
	old = 0
	while old != len(holdGold):
		old = len(holdGold)
		for b, l in bags.items():
			for v in holdGold:
				if v in [x[0] for x in l]:
					holdGold.add(b)
					break

	p1 = len(holdGold)-1
	p2 = recurseSum(bags, "shiny gold")-1
	return (p1, p2)