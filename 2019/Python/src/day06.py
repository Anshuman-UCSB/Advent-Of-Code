from utils.aocUtils import *
from collections import defaultdict

def p1s(children, node, depth = 0):
	return depth + sum(map(lambda x: p1s(children, x, depth+1), children[node]))

def getPath(parent, node):
	if node == 'COM':
		return []
	else:
		return getPath(parent, parent[node])+[parent[node]]

def main(input:str):
	children = defaultdict(list)
	parent = {}
	for l in input.splitlines():
		b, o = l.split(")")
		children[b].append(o)
		parent[o] = b
	# print(children)
	p1 = p1s(children, "COM")
	p2 = len(set(getPath(parent, "YOU")).symmetric_difference(set(getPath(parent, "SAN"))))
	return (p1, p2)