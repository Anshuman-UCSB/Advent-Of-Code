from utils.aocUtils import *
from collections import deque

def turn(player, crab):
	p = player.popleft()
	c = crab.popleft()
	if p>c:
		player.append(p)
		player.append(c)
	else:
		crab.append(c)
		crab.append(p)

def turn2(player, crab):
	p = player.popleft()
	c = crab.popleft()
	if len(player)>=p and len(crab)>=c:
		# print(p, c)
		# print(player, crab)
		winner = game(deque(list(player)[:p]), deque(list(crab)[:c]))[0]
		if winner == "player":
			player.append(p)
			player.append(c)
		else:
			crab.append(c)
			crab.append(p)	
	else:
		if p>c:
			player.append(p)
			player.append(c)
		else:
			crab.append(c)
			crab.append(p)

def game(player, crab):
	# print("p: ",player)
	# print("c: ",crab)
	cache = set()
	# cache.add(str(player)+str(crab))
	while len(player) > 0 and len(crab)>0:
		hash = str(player)+str(crab)
		if hash in cache:
			return ("player", player, crab) #player won
		cache.add(hash)
		turn2(player, crab)
	return ("player" if len(player)>0 else "crab", player, crab)


def getScore(player):
	player = list(player)[::-1]
	out = 0
	for i in range(len(player)):
		out+=(i+1)*player[i]
	return out

def main(input:str):
	chunks = input.split("\n\n")
	player = deque()
	crab = deque()
	for l in chunks[0].splitlines()[1:]:
		player.append(int(l))
	for l in chunks[1].splitlines()[1:]:
		crab.append(int(l))
	_, p, c = game(player.copy(), crab.copy())
	while len(player) > 0 and len(crab)>0:
		turn(player, crab)
	p1 = max(getScore(player), getScore(crab))
	p2 = max(getScore(p), getScore(c))
	return (p1, p2)