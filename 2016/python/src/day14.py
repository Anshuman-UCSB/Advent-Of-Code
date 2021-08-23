# from hashlib import md5
from _md5 import md5

cache = {}
def hash(inp):
	if inp in cache:
		return cache[inp]
	cache[inp] = str(md5(inp.encode()).hexdigest())
	return cache[inp]

cache2 = {}
def hash2(inp):
	if inp in cache2.keys():
		return cache2[inp]
	t = inp
	for _ in range(2017):
		t = hash(str(t))
	cache2[inp] = t
	return t

def consec5(inp, ch):
	comp = ch * 5
	for i in range(len(inp)-4):
		if inp[i:i+5] == comp:
			return True
	return False
		
def consec3(inp):
	for i in range(len(inp)-2):
		if len(set(inp[i:i+3])) == 1:
			return inp[i]
	return None

def isValid( inp, pos, c):
	for i in range(pos+1, pos+1001):
		h = hash(inp+str(i))
		if consec5(h, c): return True
	return False
def isValid2( inp, pos, c):
	for i in range(pos+1, pos+1000):
		if consec5(hash2(inp+str(i)), c): return True
	return False

def main(inp:str) -> tuple:
	hashlist = []
	p1 = -1
	for _ in range(64):
		while True:
			p1+=1
			h = hash(inp+str(p1))
			ch = consec3(h)
			if ch and isValid(inp, p1, ch):
				# print(_+1, p1)
				break
	p2 = -1
	for _ in range(64):
		while True:
			p2+=1
			h = hash2(inp+str(p2))
			ch = consec3(h)
			# if ch:
				# print(p2,h)
			if ch and isValid2(inp, p2, ch):
				# print(_, p2)
				break
				
	return (p1, p2)
