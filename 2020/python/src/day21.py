from utils.aocUtils import *
from collections import defaultdict

def main(input:str):
	counter = defaultdict(int)
	foods = {}
	for l in input.splitlines():
		lhs, rhs = l.split(" (")
		for l in lhs.split():
			counter[l]+=1
		ingredients = set(lhs.split())
		allergens = set()
		for w in rhs.split()[1:]:
			allergens.add(w[:-1])
		# print(ingredients, allergens)
		for a in allergens:
			if a not in foods:
				foods[a] = ingredients
			else:
				foods[a] = foods[a].intersection(ingredients)
	done = False
	solved = set()
	m = {}
	while not done:
		done = True
		for a, i in foods.items():
			i = i.difference(solved)
			# print(a, i)
			if len(i) == 1:
				done = False
				solved.add(list(i)[0])
				m[list(i)[0]] = a
	p1 = (sum([v for x, v in counter.items() if x not in solved]))
	p2 = ",".join([x[0] for x in sorted(list(m.items()), key = lambda x: x[1])])
	return (p1, p2)