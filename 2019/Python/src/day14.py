from utils.aocUtils import *
from collections import defaultdict
import numpy as np
import re
from math import ceil

def make(resource, recipies, item):
	# print(item)
	name, cnt = item
	recAmt, recipie = recipies[item[0]]
	mul = ceil(cnt/recAmt)
	resource[name]+=mul*recAmt
	for need in recipie:
		resource[need[0]]-=mul*need[1]
	for n, c in resource.items():
		if c<0 and n!="ORE":
			make(resource, recipies, (n, -c))

def oreReq(recipies, blankDict, fuelcount):
	t = blankDict.copy()
	make(t, recipies, ("FUEL", fuelcount))
	return -t['ORE']


def p2s(recipies, blankDict):
	t = blankDict.copy()
	make(t, recipies, ("FUEL", 1))
	while t['ORE']> -1e12:
		make(t, recipies, ("FUEL", t['FUEL']))
	l = t['FUEL']//2
	h = t['FUEL']
	while l<h:
		m = (l+h)>>1
		if oreReq(recipies, blankDict, m) > 1e12:
			h = m
		else:
			l = m+1
	return l-1
	

def main(input:str):
	resource = {}
	recipies = {}
	for l in input.splitlines():
		matches = [(b,int(a)) for a, b in re.findall(r"(\d+) (\w+)", l)]
		recipies[matches[-1][0]] = (matches[-1][1],matches[:-1])
		for m in matches:
			resource[m[0]] = 0
	# print(resource)
	blankDict = resource.copy()
	make(resource, recipies, ("FUEL", 1))
	# print(resource)
	p1 = -resource["ORE"]
	p2 = p2s(recipies, blankDict)
	return (p1, p2)