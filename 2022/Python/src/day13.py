from utils.aocUtils import *

def spaceship(a, b):
	if a<b: return True
	elif a == b: return None
	else: return False

def compare(a, b):
	if isinstance(a, int) and isinstance(b, int):
			return spaceship(a,b)
	if isinstance(a, int):	a = [a]
	if isinstance(b, int):	b = [b]
	for i in range(min(len(a), len(b))):
		res = compare(a[i], b[i])
		if res != None:		return res
	return spaceship(len(a),len(b))

class Packet:
	def __init__(self, line):
		self.arr = eval(line)
	def __lt__(self, other):
		return compare(self.arr, other.arr)
	def __len__(self):	return len(self.arr)
	def __str__(self):	return str(self.arr)

def main(input:str):
	p1 = 0
	inp = []
	for l in input.splitlines():
		if l != "":
			inp.append(Packet(l))
	for ind in range(0,len(inp),2):
		if inp[ind]<inp[ind+1]:
			p1+=ind//2+1
	inp.extend([Packet("[[2]]"), Packet("[[6]]")])
	p2 = 1
	for i, v in enumerate(sorted(inp)):
		if str(v) in ("[[2]]", "[[6]]"):
			p2*=i+1
	return (p1, p2)