from utils.aocUtils import *
from itertools import product

class Dice:
	def __init__(self):
		self.n = 0
		self.rolls =0

	def roll(self):
		out = mod(self.n+1,100)+mod(self.n+2,100)+mod(self.n+3,100)
		self.n = (self.n+3)%100
		self.rolls+=3
		return out

@cache
def mod(n, base=10):
	return (n-1)%base+1

class player:
	def __init__(self, pos):
		self.pos = pos
		self.score = 0
	def turn(self, dice):
		self.pos = mod(self.pos+dice.roll())
		self.score+=self.pos

possibles = [sum(c) for c in product(range(1,4), repeat=3)]
@cache
def play(p1pos, p1score, p2pos, p2score, turn):
	if p1score>=21:
		return 1
	elif p2score>=21:
		return 1j
	else:
		s = 0
		if turn == 0:
			for roll in possibles:
				s+=play(mod(p1pos+roll), p1score+mod(p1pos+roll), p2pos, p2score, 1)
		elif turn == 1:
			for roll in possibles:
				s+=play(p1pos, p1score,mod(p2pos+roll), p2score+mod(p2pos+roll), 0)
		return s
			

def main(input:str):
	nums = readNums(input)
	player1 = player(nums[1])
	player2 = player(nums[3])
	d = Dice()
	p1t = True
	while player1.score<1000 and player2.score<1000:
		if p1t:
			player1.turn(d)
		else:
			player2.turn(d)
		p1t = not p1t

	p1 = min(player1.score, player2.score)*d.rolls
	p2=play(nums[1], 0, nums[3], 0, 0)
	
	return (p1, max(im2tup(p2)))