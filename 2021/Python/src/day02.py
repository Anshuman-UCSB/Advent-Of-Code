from utils.aocUtils import *
def main(input:str):
	pos1 = pos2 = aim = 0
	dir = {"forward": 1, "down":-1j, "up":1j}
	for l in input.splitlines():
		direction, dist = l.split()
		dist = int(dist)
		if direction == "down":
			aim += dist
		elif direction == "up":
			aim -= dist
		else:
			pos2+=dist
			pos2+=1j*dist*aim
		pos1 += dir[direction]*dist
	p1 = im2prod(pos1)
	p2 = im2prod(pos2)
	return (p1, p2)