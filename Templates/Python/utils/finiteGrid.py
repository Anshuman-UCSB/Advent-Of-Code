from utils.grid import *
from utils.disjointset import *

class finiteGrid(GridType):
	def __init__(self, points):
		self.g = points # points is a dictionary of imaginary numbers
						# use gridify(input) for ex
	
	def getNeighbors(self, p):
		yield from [p+1, p-1, p+1j, p-1j]

	def connComponents(self, fun):
		assert(callable(fun)) #must be callable
		ds = DisjointSet(self.g)
		for p in ds.parents:
			for n in self.getNeighbors(p):
				if n in self.g and fun(self.g[p], self.g[n]):
					ds.union(p, n)
		return ds.getSets()