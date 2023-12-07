from collections import Counter

def translate(c, part1 = True):
	if c.isnumeric():
		return int(c)
	return {
		"T":10,
		"J":11 if part1 else 1,
		"Q":12,
		"K":13,
		"A":14
	}[c]

class Hand:
	def __init__(self, line, part1 = True):
		raw, bid = line.split()
		self.bid = int(bid)
		self.cards = tuple(translate(c, part1) for c in raw)
		self.type = self.getType(part1)
	def getType(self, part1):
		counter = Counter(self.cards)
		highest = max(counter.values())
		if part1 == False:
			wilds = counter[1]
			del counter[1]
			highest = wilds
			if counter:
				highest += max(counter.values())

		if highest == 5:
			return 6 # Five of a kind
		elif highest == 4:
			return 5 # Four of a kind
		elif len(counter) == 2:
			return 4 # Full house
		elif highest == 3:
			return 3 # Three of a kind
		elif len(counter) == 3:
			return 2 # Two pair
		elif highest == 2:
			return 1 # One pair
		else:
			return 0 # High card
	def __lt__(self, other):
		return self.type < other.type or (self.type == other.type and self.cards < other.cards)
	def __repr__(self):
		return str(self.cards)+"["+str(self.bid)+"]"

def solve(input, part1):
	hands = [Hand(l, part1) for l in input.splitlines()]
	hands.sort()
	ans = 0
	for i,hand in enumerate(hands):
		ans += (i+1)*hand.bid
	return ans

def main(input):

	return solve(input, True), solve(input, False)