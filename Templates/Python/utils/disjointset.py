from collections import defaultdict

class DisjointSet():
	def __init__(self, nodes):
		self.parents = {n:n for n in nodes}
	
	def find(self, node):
		if self.parents[node] == node:
			return node
		self.parents[node]=self.find(self.parents[node])
		return self.parents[node]

	def union(self, nodeA, nodeB):
		self.parents[self.find(nodeA)] = self.find(nodeB)

	def __str__(self):
		delim = ""
		out = ""
		sets = defaultdict(list)
		for k in self.parents.keys():
			sets[self.find(k)].append(k)
		for v in sets.values():
			out+=delim+"{"+str(v)[1:-1]+"}"
			delim = "\n"
		return out