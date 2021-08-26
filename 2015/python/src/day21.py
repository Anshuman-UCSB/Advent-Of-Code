from utils.aocUtils import readNums, powerset
from itertools import combinations
from functools import reduce

def simulate(player, boss):
	hp, dmg, arm = player
	bHp, bDmg, bArm = boss

	if dmg == 0:
		return False
	while True:
		bHp -= max(1, dmg-bArm)
		if bHp <=0:
			return True
		hp -= max(1, bDmg-arm)
		if hp <=0:
			return False

def main(input:str) -> tuple:
	weapons = [
		(8,4,0),
		(10,5,0),
		(25,6,0),
		(40,7,0),
		(74,8,0)
	]

	armor = [
		(13,0,1),
		(31,0,2),
		(53,0,3),
		(75,0,4),
		(102,0,5)
	]
	
	rings = [
		(25,1,0),
		(50,2,0),
		(100,3,0),
		(20,0,1),
		(40,0,2),
		(80,0,3)
	]

	wChoices = weapons
	aChoices = list(map(lambda x:x[0],combinations(armor, 1))) + [(0,0,0)]
	rChoices = [x if x else [(0,0,0)] for x in powerset(rings) if len(x)<=2]
	allChoices = []
	def addTup(base, tup):
		for i in range(3):
			base[i]+=tup[i]
	for w in wChoices:
		for a in aChoices:
			for r in rChoices:
				t = [0,0,0]
				for ring in r:
					addTup(t, ring)
				addTup(t, a)
				addTup(t, w)
				allChoices.append(t)

	allChoices.sort(key=lambda x: x[0])
	boss = tuple(readNums(input))
	for p in allChoices:
		if simulate((100,p[1],p[2]), boss):
			p1 = p[0]
			break
	for p in allChoices[::-1]:
		if not simulate((100,p[1],p[2]), boss):
			p2 = p[0]
			break


	# print(simulate(player,boss))
	return (p1, p2)