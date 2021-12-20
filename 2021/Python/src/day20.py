import numpy as np
from scipy.ndimage import convolve

# code from /u/4HbQ
def main(input):
	algo, _, *img = input.splitlines()
	algo = np.array([int(p=='#') for p in algo])
	img = np.pad([[int(p=='#') for p in row] for row in img], (51, 51))
	bin2dec = 2**np.arange(9).reshape(3,3)
	for i in range(50):
		img = algo[convolve(img, bin2dec)]
		if i==1:
			p1 = img.sum()
	return p1, img.sum()


from utils.aocUtils import *
def OLD(input:str):
	alg, img = input.split("\n\n")
	img = set(p for p,v in gridify(img).items() if v == '#')
	neighbors = [-1-1j,-1j,1-1j,-1,0,1,-1+1j,1j,1+1j]
	def logic(p, img, isLights = 1, default = 0):
		b = 0
		for n in neighbors:
			b*=2
			if p+n in img:
				b+=isLights
			else:
				b+=default
		return alg[b]=='#'
	def considers(img):
		lx = ly = hx = hy = 0
		for p in img:
			lx = int(min(lx, p.real))
			ly = int(min(ly, p.imag))
			hx = int(max(hx, p.real))
			hy = int(max(hy, p.imag))
		for y in range(ly-5, hy+5):
			for x in range(lx-5, hx+5):
				yield x+1j*y
	def iter2():
		unlit = set()
		for p in considers(img):
			if logic(p, img) == False:
				unlit.add(p)
		lit = set()
		for p in considers(unlit):
			if logic(p, unlit, 0, 1):
				lit.add(p)
		return lit
	for it in range(25):
		img = iter2()
		if it == 0:
			p1 = len(img)
	p2 = len(img)
	return (p1, p2)