childrenNodes = set()
class Node:
	def __init__(self, line):
		global childrenNodes
		spl=line.split()
		self.name = spl[0]
		self.weight = int(spl[1][1:-1])
		self.children = list(map(lambda x: x.replace(',',''),spl[3:]))
		childrenNodes|=set(self.children)
		self.cumWeight = None
	def getCumWeight(self):
		if self.cumWeight == None:
			self.cumWeight = self.weight
			for c in self.children:
				self.cumWeight+=c.getCumWeight()
		return self.cumWeight
	def updateChildren(self,T):
		self.children = [T[c] for c in self.children]
	def isBalanced(self):
		childWeights = [c.getCumWeight() for c in self.children]
		return len(set(childWeights)) <= 1
	def __repr__(self):
		return f"Node {self.name} ({self.weight}) with {len(self.children)} children"
def day7(input):
	T={}
	for l in input.splitlines():
		N = Node(l)
		T[N.name]=N
	for n in T.values():
		n.updateChildren(T)
	parent ,= set(T.keys())-childrenNodes
	p = T[parent]
	targetWeight = None
	while not p.isBalanced():
		balancedChildren = True
		for c in p.children:
			if not c.isBalanced():
				p = c
				balancedChildren=False
			else:
				targetWeight = c.getCumWeight()
		if balancedChildren:
			break
	
	print(targetWeight)
	print(p)
	return [parent,p.getCumWeight()-targetWeight]