from itertools import product

def expand(rules:dict, cache:dict, limit):
	while '0' not in cache:
		for num,rule in rules.items():
			if num in cache: continue
			cacheable = True
			for r in rule:
				if all([x in cache for x in r]) == False:
					cacheable = False
					break
			if cacheable:
				solution = set()
				for r in rule:
					tmp = []
					for tok in r:
						tmp.append(cache[tok])
					print(tmp, rule)
					for combo in product(*tmp):
						to_add = "".join(combo)
						if len(to_add)<=limit:
							solution.add(to_add)
				cache[num] = solution
def main(input):
	global solved
	solved = {}
	rules_raw,messages = input.split('\n\n')
	messages = set(messages.splitlines())
	limit = max(map(len, messages))
	assert len(messages) == len(input.split('\n\n')[1].splitlines())
	rules = {}
	cache = {}
	cache2 = {}
	for l in rules_raw.splitlines():
		if '"' in l:
			rules[l.split(':')[0]] = [l.split(':')[1][2]]
			cache[l.split(':')[0]] = (l.split(':')[1][2],)
			cache2[l.split(':')[0]] = (l.split(':')[1][2],)
		else:
			rules[l.split(':')[0]] = list(map(lambda x:x.split(),l.split(':')[1].split('|')))
	expand(rules, cache, limit)
	p1 = len(set(messages) & cache['0'])
	print(rules['1'])
	rules['11'] = [['42']*n + ['31']*n for n in range(1,3)]
	print(rules['11'])
	expand(rules, cache2, limit)
	p2 = len(set(messages) & cache2['0'])
	return p1, p2

# 102
# 318
# def replace(tokenized, o, n):
# 	return [n if x == o else x for x in tokenized]

# def expand(rule:str, rules:dict, limit):
# 	# if rule in solved:
# 	# 	print("cached in solved:", solved)
# 	# 	return solved[rule]
# 	if len(rule.split())>limit:
# 		return set()
# 	if set(rule) == {'a','b',' '}:
# 		solved[rule] = {rule}
# 		return {rule}
# 	else:
# 		rep = None
# 		for token in rule.split():
# 			if token not in "ab":
# 				rep = token
# 				break
# 		generated = {rereplace(rule,token, r) for r in rules[token]}
# 		out = set()
# 		for g in generated:
# 			out|=expand(g, rules,limit)
# 		solved[rule] = out
# 		return out
