from utils.aocUtils import *
import numpy as np

directions = ((-1,0), (0,-1),(1,0), (0,1))

def explore(grid, x, y):
	visible = False
	score = 1
	val = grid[y,x]
	sz = grid.shape[0]
	for dy, dx in directions:
		i = 0
		tx,ty = x+dx,y+dy
		while 0<=tx<sz and 0<=ty<sz:
			i+=1
			if grid[ty,tx] >= val:
				break
			tx+=dx
			ty+=dy
		visible |= not (0<=tx<sz and 0<=ty<sz)
		score*=i
	return visible,score

def main(input:str):
	p1 = p2 = 0
	grid = []
	for l in input.splitlines():
		grid.append(list(map(int, l)))
	grid = np.array(grid)
	sz = grid.shape[0]
	for r in range(sz):
		for c in range(sz):
			visible, score = explore(grid, r, c)
			p2 = max(score, p2)
			p1 += visible
	
	return (p1, p2)