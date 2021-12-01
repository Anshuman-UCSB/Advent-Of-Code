from utils.aocUtils import *
import re
import math
from collections import defaultdict

recipies = defaultdict(list)
amounts = {}
def chunks(lst, n):
    """Yield successive n-sized chunks from lst."""
    for i in range(0, len(lst), n):
        yield lst[i:i + n]
def makeRecipie(line):
	spl = line.split()
	amounts[spl[-1]] = int(spl[-2])
	parent = spl[-1]
	spl = line.split(" => ")[0].split()
	for num, name in chunks(spl, 2):
		recipies[parent].append((int(num), name.replace(",", "")))

def getOreCost(recipies, amount, fuelCount):
	def make(reagent):
		num, name = reagent
		recipieCount = math.ceil(num/amounts[name])
		ingredients[name]+=amounts[name]*recipieCount
		for ingred in recipies[name]:
			ingredients[ingred[1]] -= recipieCount*ingred[0]
		# q = []
		for n, v in ingredients.items():
			if n != "ORE" and v < 0:
				make((-v, n))

	ingredients = {}
	for n, r in recipies.items():
		ingredients[n] = 0
		for _,v in r:
			ingredients[v] = 0
	make((fuelCount, "FUEL"))
	return -1*ingredients["ORE"]
def main(input:str):
	for l in input.splitlines():
		makeRecipie(l)
	
	p1 = getOreCost(recipies, amounts, 1)
	p2Limit = 1000000000000
	l, h = 0, 10000000
	while l<h:
		m = (l+h)//2
		if getOreCost(recipies, amounts, m) > p2Limit:
			h = m
		else:
			l = m+1
	p2 = l-1
	return (p1, p2)