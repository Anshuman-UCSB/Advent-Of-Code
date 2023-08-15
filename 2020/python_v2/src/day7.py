def count_contained(bag, bags_contained, structure):
	if bag in bags_contained:
		return bags_contained[bag]
	count = 0
	for child, num in structure[bag].items():
		count+=num*(1+count_contained(child, bags_contained, structure))
	bags_contained[bag] = count
	return count
def main(input):
	structure = {}
	for l in input.splitlines():
		main, contains = l[:-1].split(' bags contain ')
		contains=contains.replace(" bags",'')
		contains=contains.replace(" bag",'')
		structure[main] = {}
		if contains != 'no other':
			structure[main] = dict(map(lambda x: (x[2:],int(x.split(' ')[0])), contains.split(', ')))
	dont_contain = set(structure) - {"shiny gold"}
	contain = {"shiny gold"}
	changed = True
	while changed:
		changed = False
		for dont in dont_contain:
			if set(structure[dont])&contain:
				contain.add(dont)
				dont_contain.remove(dont)
				changed = True
				break
	bags_contained = {}
	return len(contain)-1, count_contained('shiny gold', bags_contained, structure)