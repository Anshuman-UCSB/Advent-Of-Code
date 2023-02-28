def day12(input):
	# UNION FIND MY BELOVED
	groups = [*range(len(input.splitlines()))]
	def find(a):
		if a==groups[a]:
			return a
		groups[a]=find(groups[a])
		return groups[a]
	def join(a,b):
		p = find(a)
		groups[find(b)] = p
		
	for l in input.splitlines():
		lhs,rhs=l.split('<->')
		for v in map(int,rhs.split(',')):
			join(int(lhs),v)
	for i in range(len(groups)):
		find(i)
	return [groups.count(groups[0]),len(set(groups))]