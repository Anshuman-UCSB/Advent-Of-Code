from copy import copy
class Game:
	def __init__(self, p1, p2):
		self.p1 = p1
		self.p2 = p2
	def play(self):
		while self.p1 and self.p2:
			c1, c2 = map(lambda x: x.pop(0), (self.p1, self.p2))
			if c1 > c2:
				self.p1.extend([c1, c2])
			else:
				self.p2.extend([c2, c1])
		score = 0
		for i in range(1, len(self.p1)+1):
			score += self.p1[-i]*i
		for i in range(1, len(self.p2)+1):
			score += self.p2[-i]*i
		return score
	def __str__(self):
		return f"{self.p1}\n{self.p2}"

class Game2:
	def __init__(self, p1, p2, layer = 0):
		self.p1 = copy(p1)
		self.p2 = copy(p2)
		self.cache = set()
		self.layer = layer
	def hash(self):
		return str(self.p1)
	def winner(self):
		if self.hash() in self.cache:
			return 1
		if self.layer > 0 and max(self.p1) > max(self.p2):
			return 1
		self.cache.add(self.hash())
		c1, c2 = self.p1[0], self.p2[0]
		if len(self.p1)-1 >= c1 and len(self.p2)-1 >= c2:
			ng = Game2(self.p1[1:1+c1],self.p2[1:1+c2],self.layer+1)
			ng.play()
			ans = 1 if ng.p1 else 2
			return ans
		else:
			ans = 1 if c1 > c2 else 2
			return ans
	def play(self):
		while self.p1 and self.p2:
			if self.winner() == 1:
				c1, c2 = map(lambda x: x.pop(0), (self.p1, self.p2))
				self.p1+=[c1,c2]
			else:
				c1, c2 = map(lambda x: x.pop(0), (self.p1, self.p2))
				self.p2+=[c2,c1]
		score = 0
		for i in range(1, len(self.p1)+1):
			score += self.p1[-i]*i
		for i in range(1, len(self.p2)+1):
			score += self.p2[-i]*i
		return score
	def __str__(self):
		return f"{' '*(self.layer)}{self.p1}\n{' '*(self.layer+1)}{self.p2}"
				

def main(input):
	player1, player2 = input.split("\n\n")
	p1 = list(map(int, player1.splitlines()[1:]))
	p2 = list(map(int, player2.splitlines()[1:]))
	g = Game(p1, p2)
	g2 = Game2(p1, p2)
	return g.play(), g2.play()

# 31379 too high
# 29177 is answer