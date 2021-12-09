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

	def getSets(self):
		for n in self.parents:
			self.find(n)
		uniq = set(self.parents.values())
		out = defaultdict(list)
		for n in self.parents:
			out[self.find(n)].append(n)
		# print(out)
		return [set(x) for x in out.values()]

	def __str__(self):
		out = ""
		delim = ""
		for v in self.getSets():
			out+=delim+str(v)
			delim="\n"
		return out