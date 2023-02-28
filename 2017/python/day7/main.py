from collections import Counter
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
		self.balanced = None
	def getCumWeight(self):
		if self.cumWeight == None:
			self.cumWeight = self.weight
			for c in self.children:
				self.cumWeight+=c.getCumWeight()
		return self.cumWeight
	def updateChildren(self,T):
		self.children = [T[c] for c in self.children]
	def isBalanced(self):
		if self.balanced == None:
			childWeights = [c.getCumWeight() for c in self.children]
			self.balanced = len(set(childWeights)) <= 1
		return self.balanced
def day7(input):
	T={}
	for l in input.splitlines():
		N = Node(l)
		T[N.name]=N
	for n in T.values():
		n.updateChildren(T)
	parent ,= set(T.keys())-childrenNodes
	p = T[parent]
	target=0
	while not p.isBalanced():
		weights = Counter()
		weight_nodes = {}
		for c in p.children:
			if not c.isBalanced():
				p = c
				break
			else:
				weights[c.getCumWeight()]+=1
				weight_nodes[c.getCumWeight()] = c
		if sum(weights.values())==len(p.children):
			# all children nodes were balanced
			(target,_),(actual,_)=weights.most_common()
			p2 = target-actual+weight_nodes[actual].weight
			break
	return [parent,p2]