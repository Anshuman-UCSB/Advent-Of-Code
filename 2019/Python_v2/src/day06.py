from utils.aocUtils import *

def getPath(start, parents):
	path = set()
	while start != "COM":
		path.add(start)
		start = parents[start]
	return path

def main(input:str):
	parents = {}
	for l in input.splitlines():
		p, c = l.split(")")
		parents[c] = p
	orbitDist= {"COM":0}

	
	while len(orbitDist) <= len(parents):
		for c, p in parents.items():
			if p in orbitDist:
				orbitDist[c] = orbitDist[p]+1
	
	

	p1 = sum(orbitDist.values())
	p2 = len(getPath("YOU", parents).symmetric_difference(getPath("SAN", parents)))-2
	return (p1, p2)