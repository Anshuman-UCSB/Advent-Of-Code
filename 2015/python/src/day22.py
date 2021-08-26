from utils.aocUtils import readNums
from queue import PriorityQueue
from copy import deepcopy
from random import random

cache = set()

class Player:
	def __init__(self, hp, mana, boss):
		self.hp = hp
		self.mana = mana
		self.armor = 0
		self.spentMana = 0
		self.effects = []
		self.boss = boss #hp, dmg
		self.castOrder = []

	def __cmp__(self, other):
		return cmp((self.spentMana, self.boss[0], self.hp), (other.spentMana, other.boss[0], other.hp))


	def missile(self):
		self.mana -= 53
		self.spentMana += 53
		self.boss[0]-=4
		self.castOrder.append("missile")

	def drain(self):
		self.mana -= 73
		self.spentMana += 73
		self.boss[0]-=2
		self.hp+=2
		self.castOrder.append("drain")

	def shield(self):
		self.mana -= 113
		self.spentMana += 113
		self.effects.append([6, "shield"])
		self.castOrder.append("shield")
	
	def poison(self):
		self.mana -= 173
		self.spentMana += 173
		self.effects.append([6, "poison"])
		self.castOrder.append("poison")
	
	def recharge(self):
		self.mana -= 229
		self.spentMana += 229
		self.effects.append([5, "recharge"])
		self.castOrder.append("recharge")
	
	def processEffects(self):
		for effect in self.effects:
			effect[0]-=1
			if effect[1] == "shield":
				self.armor = 7
			elif effect[1] == "poison":
				self.boss[0]-=3
			elif effect[1] == "recharge":
				self.mana+=101
		for i in range(len(self.effects)-1, -1, -1):
			if self.effects[i][0] ==0:
				if self.effects[i][1] == "shield":
					self.armor = 0
				del self.effects[i]
	def print(self):
		print(f"\nPlayer has {self.hp} hp, {self.armor} armor, {self.mana} mana.")
		print(f"Boss has {self.boss[0]} hp.")
		if self.effects:
			print("Current effects:")
		for e in self.effects:
			print("	",e[1],f"({e[0]})")

	def turn(self, choice):
		choice()
		if self.boss[0]<=0:
			return "Player"

		self.processEffects()
		if self.boss[0]<=0:
			return "Player"
		self.hp -= max(1, self.boss[1]-self.armor)
		if self.hp<=0:
			return "Boss"
		return None

	def hash(self):
		return (self.hp, self.spentMana, self.mana, self.boss[0], str(sorted(self.effects)))

	def iter(self, q):
		h = self.hash()
		if h not in cache:
			cache.add(h)
			self.processEffects()
			# print(self.effects)
			if self.mana >= 53:
				t = deepcopy(self)
				res = t.turn(t.missile)
				if res == "Player":
					return t.spentMana
				elif res == None: pushQ(q, t)
			if self.mana >= 73:
				t = deepcopy(self)
				res = t.turn(t.drain)
				if res == "Player":
					return t.spentMana
				elif res == None: pushQ(q, t)
			if self.mana >= 113 and "shield" not in [x for _, x in self.effects]:
				t = deepcopy(self)
				res = t.turn(t.shield)
				if res == "Player":
					return t.spentMana
				elif res == None: pushQ(q, t)
			if self.mana >= 173 and "poison" not in [x for _, x in self.effects]:
				t = deepcopy(self)
				res = t.turn(t.poison)
				if res == "Player":
					return t.spentMana
				elif res == None: pushQ(q, t)
			if self.mana >= 229 and "recharge" not in [x for _, x in self.effects]:
				t = deepcopy(self)
				res = t.turn(t.recharge)
				if res == "Player":
					return t.spentMana
				elif res == None: pushQ(q, t)
		

def pushQ(q, player):
	t = deepcopy(player)
	q.put((t.spentMana, t.boss[0], t.hp, t.effects, t.armor, random(), t))

def testExample():
	base = Player(10,250, [14,8])
	base.turn(base.recharge)
	base.print()
	base.turn(base.shield)
	base.print()
	base.turn(base.drain)
	base.print()
	base.turn(base.poison)
	base.print()
	base.turn(base.missile)
	base.print()

def testManual():
	#['P', 'R', 'S', 'P', 'R', 'S', 'P', 'R', 'S', 'P', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M', 'M']
	boss = [71,10]
	base = Player(50,500, boss)
	moves = [base.missile, base.drain, base.shield, base.poison, base.recharge]
	order = [3,4,2,3,4,2,3,4,2,3,0,0]
	for o in order:
		base.turn(moves[o])
		base.print()
	print(base.spentMana)

def main(input:str) -> tuple:
	boss = readNums(input)
	base = Player(50,500, boss)
	q = PriorityQueue()
	pushQ(q, base)
	while not q.empty():
		t = q.get()[-1]
		res = t.iter(q)
		if res != None:
			p1 = res
			break
	return (p1, 0)