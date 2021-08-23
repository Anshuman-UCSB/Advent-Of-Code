from _md5 import md5
from collections import deque
from time import sleep

def hash(inp):
	return md5(inp.encode()).hexdigest()

def getValidDoors(path):
	h = hash(path)[:4]
	return [path+"UDLR"[i] for i in range(4) if h[i]>'a']

def getPos(path):
	x, y = 0, 0
	for c in path:
		if c == 'U':
			y-=1
		elif c == 'D':
			y+=1
		if c == 'L':
			x-=1
		elif c == 'R':
			x+=1
	return (x,y)

def isEnd(path):
	return getPos(path) == (3,3)

def main(input:str) -> tuple:
	q = deque()
	p1 = None
	p2 = ""
	q.append(input)
	while(len(q)>0):
		p = q.pop()
		x, y = getPos(p)
		if(x<0 or x>3 or y<0 or y>3): continue
		if(isEnd(p)):
			if(len(p)>len(p2)):
				p2 = p
			if(p1 == None or len(p)<len(p1)):
				p1 = p
		else:
			for path in getValidDoors(p):
				q.append(path)
		# print(p1, len(p2))
		# sleep(.1)
			
	return (p1[len(input):], len(p2)-len(input))
