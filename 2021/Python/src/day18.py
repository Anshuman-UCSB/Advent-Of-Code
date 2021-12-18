from utils.aocUtils import *
from itertools import combinations

class Node:
	def __init__(self, val, depth = 0, parent = None):
		if type(val) == list:
			self.pair = True
			self.left, self.right = Node(val[0], depth+1, self), Node(val[1], depth+1, self)
		else:
			self.pair = False
			self.val = val
		self.parent = parent
		self.depth = depth

	def isRight(self):
		return self.parent and self.parent.right == self
	def isLeft(self):
		return self.parent and self.parent.left == self

	def successor(self):
		p = self
		while p.parent and p.isRight():
			p = p.parent
		p = p.parent
		if p:
			p = p.right
			while p.pair:
				p = p.left
			return p
		return None
	def predecessor(self):
		p = self
		while p.parent and p.isLeft():
			p = p.parent
		p = p.parent
		if p:
			p = p.left
			while p.pair:
				p = p.right
			return p
		return None
	
	def explode(self):
		if self.pair and self.depth>=4:
			p = self.predecessor()
			if p:
				p.val+=self.left.val
			p = self.successor()
			if p:
				p.val+=self.right.val
			self.pair = False
			self.val = 0
			return True
		else:
			if self.pair:
				return self.left.explode() or self.right.explode()
			return False

	def split(self):
		if self.pair:
			return self.left.split() or self.right.split()
		else:
			if self.val >= 10:
				self.pair = True
				self.left = Node(self.val//2, self.depth+1, self)
				self.right = Node(self.val//2+(self.val%2), self.depth+1, self)
				return True
			return False

	def incDepth(self):
		self.depth+=1
		if self.pair:
			self.left.incDepth()
			self.right.incDepth()

	def update(self):
		while True:
			if self.explode():
				continue
			if self.split():
				continue
			break

	def __str__(self):
		if self.pair:
			return f"[{self.left},{self.right}]"
		else:
			return str(self.val)

	def magnitude(self):
		if self.pair:
			return 3*self.left.magnitude()+2*self.right.magnitude()
		else:
			return self.val

def build(inp):
	return Node(eval(inp))

def add(a, b):
	n = Node([None, None])
	n.left, n.right = a, b
	n.left.parent, n.right.parent = n, n
	n.left.incDepth()
	n.right.incDepth()
	n.update()
	return n

def main(input:str):
	n = build(input.splitlines()[0])
	for l in input.splitlines()[1:]:
		n = add(n, build(l))
	p1 = n.magnitude()
	p2 = 0
	for a, b in combinations(input.splitlines(), 2):
		p2 = max(p2, add(build(b), build(a)).magnitude(), add(build(a), build(b)).magnitude())
	return (p1, p2)