import numpy as np
import re

def main(input:str) -> tuple:
	A = np.zeros([6,50], dtype = bool)
	for l in input.splitlines():
		a, b = map(int, re.findall(r'\d+', l))
		id = l.split(' ')[1]
		if id == "row": A[a] = np.roll(A[a], b)
		elif id == "column": A.T[a] = np.roll(A.T[a], b)
		else: A[:b,:a] = True
	build = ""
	for r in A:
		build+="\n"
		for v in r:
			build+="#" if v else " "
	return (np.sum(A), build)
