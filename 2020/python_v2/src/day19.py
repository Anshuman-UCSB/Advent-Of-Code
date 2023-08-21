import re

def solve(rules, words, part2=False):
	cache = {}
	parsed = {}
	requires = {}
	for l in rules:
		lhs, rhs = l.split(": ")
		if '"' in rhs:
			cache[lhs] = rhs[1]
		else:
			parsed[lhs] = [x.split() for x in rhs.split(' | ')]
			requires[lhs] = set()
			for pos in parsed[lhs]:
				requires[lhs].update(pos)
	if part2:
		parsed['11'] = [['42']*n+['31']*n for n in range(1,6)]
	while '0' not in cache:
		for tok,req in requires.items():
			if tok in cache:continue
			if req <= cache.keys():
				tmp = []
				for rule in parsed[tok]:
					# tmp.append("".join([f"({cache[t]})" for t in rule]))
					tmp.append("".join([f"{cache[t]}" for t in rule]))
				cache[tok] = "("+"|".join(tmp)+")"
				if part2 and tok == '8':
					cache['8']+='+'
	regex = re.compile("^"+cache['0']+"$")
	return sum([regex.match(l) is not None for l in words])

def main(input):
	rules, words = map(lambda x: x.splitlines(),input.split('\n\n'))
	return solve(rules, words),solve(rules, words, True)