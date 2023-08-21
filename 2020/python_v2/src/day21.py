def main(input):
	p1 = 0
	parsed = []
	for l in input.splitlines():
		lhs, rhs = l.split(' (contains ')
		parsed.append((set(lhs.split()), {x[:-1] for x in rhs.split()}))
	allergens = {r for allergen in parsed for r in allergen[1]}
	solved = {}
	usedIngredients = set()
	while len(allergens) != len(usedIngredients):
		for a in allergens:
			if a in solved:continue
			s = None
			for p in parsed:
				if a in p[1]:
					if s == None: s = (p[0]-usedIngredients)
					else: s&=p[0]-usedIngredients
			if len(s) == 1:
				ing ,= s
				usedIngredients.add(ing)
				solved[a] = ing
	for ings,_ in parsed:
		p1 += sum(ing not in usedIngredients for ing in ings)
	p2 = []
	for a in sorted(allergens):
		p2.append(solved[a])
	return p1, ",".join(p2)