from utils.aocUtils import *
from src.intcode import *
def main(input:str):
	c = CPU(input)
	c.run()
	inp = ""
	for c in c.outputQ:
		inp += chr(c)
	grid = inp.splitlines()
	p1 = 0
	grid.pop(-1)
	for y, row in enumerate(grid):
		for x, val in enumerate(row):
			if(val == '#'):
				if (x>0 and x<len(grid[0])-1):
					if (y>0 and y<len(grid)-1):
						if(grid[y+1][x] == '#' and
						   grid[y-1][x] == '#' and
						   grid[y][x+1] == '#' and
						   grid[y][x-1] == '#'):
						   p1+=y*x
	p2 = 0
	return (p1, p2)