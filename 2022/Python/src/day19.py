from utils.aocUtils import *
import re

# Full credit to /u/Boojum, pretty much word for word stolen solution; his was just years faster than my numpy version
def parse(line):
	return list(map(int,re.findall("\d+",line)))
	
def main(input:str):
	p1,p2 = 0,1
	o = [ sum(range(n)) for n in range(35) ]
	bps = list(map(parse, input.splitlines()))
	for n, a,b,c,d,e,f in bps:
		mi,mj,mk = max(a,b,c,e), d, f
		def dfs( t, g,best,# t:time remaining, g:goal robot type, best: [bestval]
			 i, j, k, l,   # i:ore, j:clay, k:obsidian, l:geode robots
			 w, x, y, z ): # w:ore, x:clay, y:obsidian, z:geode available
			if ( g == 0 and i >= mi or
				g == 1 and j >= mj or
				g == 2 and ( k >= mk or j == 0 ) or
				g == 3 and k == 0 or
				z + l * t + o[ t ] <= best[0]):
				return
			while t:
				if g == 0 and w >= a:
					for g in range( 4 ):
						dfs(t-1, g, best, i + 1, j, k, l, w - a + i, x + j, y + k, z + l )
					return
				elif g == 1 and w >= b:
					for g in range( 4 ):
						dfs(t-1, g, best, i, j + 1, k, l, w - b + i, x + j, y + k, z + l )
					return
				elif g == 2 and w >= c and x >= d:
					for g in range( 4 ):
						dfs(t-1, g, best, i, j, k + 1, l, w - c + i, x - d + j, y + k, z + l )
					return
				elif g == 3 and w >= e and y >= f:
					for g in range( 4 ):
						dfs(t-1, g, best, i, j, k, l + 1, w - e + i, x + j, y - f + k, z + l )
					return
				t, w, x, y, z = t - 1, w + i, x + j, y + k, z + l
			best[0] = max(best[0],z)
		best = [0]
		for g in range( 4 ):
			dfs( 24, g, best, 1,0,0,0, 0,0,0,0)
		p1 += best[0] * n
		if n < 4:
			best = [0]
			for g in range( 4 ):
				dfs( 32, g, best, 1,0,0,0, 0,0,0,0)
			p2*=best[0]
	return (p1, p2)