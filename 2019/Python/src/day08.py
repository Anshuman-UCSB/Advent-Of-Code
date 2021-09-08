from utils.aocUtils import *
import numpy as np

w = 25
h = 6

def main(input:str):
	layers = [np.array(list(map(int,list(input[i:i+(w*h)])))) for i in range(0, len(input), w*h)]
	for i, a in enumerate(layers):
		layers[i] = np.reshape(a, (h,w))
			
	p1 = 0
	min0 = w*h
	for l in layers:
		if len(l[l==0])<min0:
			min0 = len(l[l==0])
			p1 = len(l[l==1])*len(l[l==2])
	p2 = [[0]*w for _ in range(h)]
	for r in layers[::-1]:
		for y in range(h):
			for x in range(w):
				if r[y][x] != 2:
					p2[y][x] = r[y][x]
		build = ""
	for i, r in enumerate(p2):
		build+='\n'
		for c in r:
			if c == 1: build+='#'
			else:	   build+=' '

	return (p1,build)