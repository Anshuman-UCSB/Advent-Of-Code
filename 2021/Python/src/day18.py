from utils.aocUtils import *
from itertools import combinations

def build(inp):
	out = []
	level = 0
	for c in inp:
		if c in '[]':
			level+= 1 if c=='[' else -1
		elif c != ',':
			out.append([int(c), level])
	return out
def split(arr):
	for i, v in enumerate(arr):
		if v[0]>=10:
			arr[i:i+1] = [[v[0]//2, v[1]+1], [v[0]//2+(v[0]%2), v[1]+1]]
			return True
def explode(arr):
	for i, (n, l) in enumerate(arr):
		if l>=5:
			if i>0:
				arr[i-1][0]+=n
			if i+2<len(arr):
				arr[i+2][0]+=arr[i+1][0]
			arr[i:i+2] = [[0, l-1]]
			return True
def update(arr):
	while True:
		if explode(arr):
			continue
		if split(arr):
			continue
		break
def magnitude(t):
	arr = t
	while True:
		for i in range(len(arr)-1):
			if arr[i][1] == arr[i+1][1]:
				arr[i:i+2] = [[3*arr[i][0]+2*arr[i+1][0], arr[i][1]-1]]
				break
		else:
			break
	return arr[0][0]
def add(a, b):
	c = [[n, l+1] for n,l in a+b]
	update(c)
	return c
def main(input:str):
	n = build(input.splitlines()[0])
	for l in input.splitlines()[1:]:
		n = add(n, build(l))
	p1 = magnitude(n)
	p2 = 0
	for a, b in combinations(input.splitlines(), 2):
		p2 = max(p2, magnitude(add(build(a), build(b))), magnitude(add(build(b), build(a))))
	return (p1, p2)