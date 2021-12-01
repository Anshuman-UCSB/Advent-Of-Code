from utils.aocUtils import *
from utils.disjointset import *
def main(input:str):
	ds = DisjointSet(range(10))
	ds.union(1,4)
	ds.union(2,5)
	ds.union(2,4)
	print(ds.parents)
	print(ds)
	p1 = 0
	p2 = 0
	return (p1, p2)