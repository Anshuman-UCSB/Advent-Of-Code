from utils.aocUtils import *

class Node:
	def __init__(self, parent = None):
		self.size = 0
		self.children = {}
		self.parent = parent
	def updateSize(self):
		for c in self.children.values():
			c.updateSize()
			self.size += c.size
	def pprint(self, ind = 0):
		print(" "*ind,"Size:",self.size)
		for n,c in self.children.items():
			print(" "*ind,"\\"+n)
			c.pprint(ind+1)
	def p1(self):
		ans = 0
		if self.size <= 100000:
			ans+=self.size
		for c in self.children.values():
			ans+=c.p1()
		return ans

sizes = []
def buildSizes(n, rootsize):
	if 40000000 >= rootsize-n.size:
		sizes.append(n.size)
	for c in n.children.values():
		buildSizes(c, rootsize)

def main(input:str):
	p1 = p2 = 0
	root = Node()
	p = root
	for l in input.splitlines():
		spl = l.split()
		if l.startswith('$ cd'):
			if spl[2] == '..':
				p = p.parent
			elif spl[2] == '/':
				p = root
			else:
				if spl[2] not in p.children:
					p.children[spl[2]] = Node(p)
				p = p.children[spl[2]]
		else:
			try:
				sz = int(spl[0])
				p.size += sz
			except ValueError:
				continue
	root.updateSize()
	buildSizes(root, root.size)
	return (root.p1(), min(sizes))