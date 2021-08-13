import re

def binary_search(f, lo=0, hi=None):
	"""
	Returns a value x such that f(x) is true.
	Based on the values of f at lo and hi.
	Assert that f(lo) != f(hi).
	"""
	lo_bool = f(lo)
	if hi is None:
		offset = 1
		while f(lo+offset) == lo_bool:
			offset *= 2
		hi = lo + offset
	else:
		assert f(hi) != lo_bool
	best_so_far = lo if lo_bool else hi
	while lo <= hi:
		mid = (hi + lo) // 2
		result = f(mid)
		if result:
			best_so_far = mid
		if result == lo_bool:
			lo = mid + 1
		else:
			hi = mid - 1
	return best_so_far


inp = """
Immune System:
5711 units each with 6662 hit points (immune to fire; weak to slashing) with an attack that does 9 bludgeoning damage at initiative 14
2108 units each with 8185 hit points (weak to radiation, bludgeoning) with an attack that does 36 slashing damage at initiative 13
1590 units each with 3940 hit points with an attack that does 24 cold damage at initiative 5
2546 units each with 6960 hit points with an attack that does 25 slashing damage at initiative 2
1084 units each with 3450 hit points (immune to bludgeoning) with an attack that does 27 slashing damage at initiative 11
265 units each with 8223 hit points (immune to radiation, bludgeoning, cold) with an attack that does 259 cold damage at initiative 12
6792 units each with 6242 hit points (immune to slashing; weak to bludgeoning, radiation) with an attack that does 9 slashing damage at initiative 18
3336 units each with 12681 hit points (weak to slashing) with an attack that does 28 fire damage at initiative 6
752 units each with 5272 hit points (immune to slashing; weak to bludgeoning, radiation) with an attack that does 69 radiation damage at initiative 4
96 units each with 7266 hit points (immune to fire) with an attack that does 738 bludgeoning damage at initiative 8

Infection:
1492 units each with 47899 hit points (weak to fire, slashing; immune to cold) with an attack that does 56 bludgeoning damage at initiative 15
3065 units each with 39751 hit points (weak to bludgeoning, slashing) with an attack that does 20 slashing damage at initiative 1
7971 units each with 35542 hit points (weak to bludgeoning, radiation) with an attack that does 8 bludgeoning damage at initiative 10
585 units each with 5936 hit points (weak to cold; immune to fire) with an attack that does 17 slashing damage at initiative 17
2449 units each with 37159 hit points (immune to cold) with an attack that does 22 cold damage at initiative 7
8897 units each with 6420 hit points (immune to bludgeoning, slashing, fire; weak to radiation) with an attack that does 1 bludgeoning damage at initiative 19
329 units each with 31704 hit points (weak to fire; immune to cold, radiation) with an attack that does 179 bludgeoning damage at initiative 16
6961 units each with 11069 hit points (weak to fire) with an attack that does 2 radiation damage at initiative 20
2837 units each with 29483 hit points (weak to cold) with an attack that does 20 bludgeoning damage at initiative 9
8714 units each with 7890 hit points with an attack that does 1 cold damage at initiative 3
""".strip()

def doit(boost=0, part1=False):
	lines = inp.splitlines()
	immune, infection = inp.split("\n\n")

	teams = []

	REGEX = re.compile(r"(\d+) units each with (\d+) hit points (\([^)]*\) )?with an attack that does (\d+) (\w+) damage at initiative (\d+)")

	# namedtuple? who needs namedtuple with hacks like these?
	UNITS, HP, DAMAGE, DTYPE, FAST, IMMUNE, WEAK = range(7)

	blah = boost
	for inps in [immune, infection]:
		lines = inps.splitlines()[1:]
		team = []
		for line in lines:
			s = REGEX.match(line)
			units, hp, extra, damage, dtype, fast = s.groups()
			immune = []
			weak = []
			if extra:
				extra = extra.rstrip(" )").lstrip("(")
				for s in extra.split("; "):
					if s.startswith("weak to "):
						weak = s[len("weak to "):].split(", ")
					elif s.startswith("immune to "):
						immune = s[len("immune to "):].split(", ")
					else:
						assert False
			u = [int(units), int(hp), int(damage) + blah, dtype, int(fast), set(immune), set(weak)]
			team.append(u)
		teams.append(team)
		blah = 0
	
	def power(t):
		return t[UNITS] * t[DAMAGE]

	def damage(attacking, defending):
		mod = 1
		if attacking[DTYPE] in defending[IMMUNE]:
			mod = 0
		elif attacking[DTYPE] in defending[WEAK]:
			mod = 2
		return power(attacking) * mod
	
	def sort_key(attacking, defending):
		return (damage(attacking, defending), power(defending), defending[FAST])
	
	while all(not all(u[UNITS] <= 0 for u in team) for team in teams):
		teams[0].sort(key=power, reverse=True)
		teams[1].sort(key=power, reverse=True)

		targets = []

		# target selection
		for team_i in range(2):
			other_team_i = 1 - team_i
			team = teams[team_i]
			other_team = teams[other_team_i]

			remaining_targets = set(i for i in range(len(other_team)) if other_team[i][UNITS] > 0)
			my_targets = [None] * len(team)

			for i, t in enumerate(team):
				if not remaining_targets:
					break
				best_target = max(remaining_targets, key= lambda i: sort_key(t, other_team[i]))
				enemy = other_team[best_target]
				if damage(t, enemy) == 0:
					continue
				my_targets[i] = best_target
				remaining_targets.remove(best_target)
			targets.append(my_targets)
		
		# attacking
		attack_sequence = [(0, i) for i in range(len(teams[0]))] + [(1, i) for i in range(len(teams[1]))]
		attack_sequence.sort(key=lambda x: teams[x[0]][x[1]][FAST], reverse=True)
		did_damage = False
		for team_i, index in attack_sequence:
			to_attack = targets[team_i][index]
			if to_attack is None:
				continue
			me = teams[team_i][index]
			other = teams[1-team_i][to_attack]

			d = damage(me, other)
			d //= other[HP]

			if teams[1-team_i][to_attack][UNITS] > 0 and d > 0:
				did_damage = True

			teams[1-team_i][to_attack][UNITS] -= d
			teams[1-team_i][to_attack][UNITS] = max(teams[1-team_i][to_attack][UNITS], 0)
		if not did_damage:
			return None
	
	if part1:
		print([x[UNITS] for x in teams[0] if x[UNITS]])
		print([x[UNITS] for x in teams[1] if x[UNITS]])
		return sum(u[UNITS] for u in teams[0]) or sum(u[UNITS] for u in teams[1])
	asd = sum(u[UNITS] for u in teams[0])
	if asd == 0:
		return None
	else:
		return asd
print(doit(part1=True))
