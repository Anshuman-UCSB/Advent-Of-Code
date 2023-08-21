from collections import Counter
def rotate(mat):
	sz = len(mat)
	tmp = [[None]*sz for _ in range(sz)]
	for y in range(sz):
		for x in range(sz):
			tmp[sz-x-1][y] = mat[y][x]
	return tmp
class Tile:
	def __init__(self, raw, orientation):
		name,*tile = raw.splitlines()
		self.id = int(name.split()[1][:-1])
		self.tile = list(map(list, tile))
		if orientation >= 4:
			self.tile = self.tile[::-1]
		for _ in range(orientation%4):
			self.tile = rotate(self.tile)
		self.orientation = orientation
		self.edges = ["".join(self.tile[0])]
		self.edges.append("".join([x[-1] for x in self.tile]))
		self.edges.append("".join(self.tile[-1]))
		self.edges.append("".join([x[0] for x in self.tile]))
	def __str__(self):
		build = str(self.id)+" "+str(self.orientation)
		for row in self.tile:
			build+='\n'+"".join(row)
		return build
def genTiles(raw):
	return [Tile(raw, i) for i in range(8)]
def buildGrid(grid):
	sz = int(len(grid)**.5)
	edgelen = len(grid[0].edges[0])-2
	g = [[None]*(sz*edgelen) for _ in range(sz*edgelen)]
	for y in range(sz):
		for x in range(sz):
			t = grid[x+y*1j]
			for yp in range(1, edgelen+1):
				for xp in range(1, edgelen+1):
					g[y*edgelen+yp-1][x*edgelen+xp-1] = t.tile[yp][xp]
	return g

def countMonsters(grid):
	match = [
		"                  # ",
		"#    ##    ##    ###",
		" #  #  #  #  #  #   "
	]
	width, height = 20, 3
	count = 0
	for y in range(len(grid)-height):
		for x in range(len(grid)-width):
			if all(match[dy][dx]!='#' or grid[y+dy][x+dx] == '#' for dy in range(height) for dx in range(width)):
				count+=1
					
	return count
def main(input):
	tiles_raw = input.split('\n\n')
	tiles = []
	for raw in tiles_raw:
		tiles+=genTiles(raw)
	c = Counter()
	for t in tiles:
		for e in t.edges:
			c[e]+=1
	losers = Counter()
	for t in tiles:
		for e in t.edges:
			if c[e] == 4:
				losers[t.id]+=1
	p1 = 1
	corner_nums = []
	for l,count in losers.items():
		if count == 16:
			p1*=l
			corner_nums.append(l)
	corner = None
	for t in tiles:
		if t.id in corner_nums and t.orientation == 0:
			score = 0
			score+= c[t.edges[0]]
			score+= c[t.edges[3]]
			if score == 8: # found top right
				corner = t
				break
	grid = {0:t}
	used = {corner.id}
	sz = int(len(tiles_raw)**.5)
	for y in range(sz-1):
		for x in range(sz):
			p = x + y*1j
			if p+1 not in grid:
				for t in tiles:
					if t.id not in used and t.edges[3] == grid[p].edges[1]:
						grid[p+1] = t
						used.add(t.id)
						break
			if p+1j not in grid:
				for t in tiles:
					if t.id not in used and t.edges[0] == grid[p].edges[2]:
						grid[p+1j] = t
						used.add(t.id)
						break
	# for y in range(sz):
	# 	for x in range(sz):
	# 		print(grid[x+y*1j].id,end='  ')
	# 	print()
	grid = buildGrid(grid)
	monsterCount = 0
	while monsterCount == 0:
	# for y, row in enumerate(rotate(grid)):
	# 	print("".join(row))
		grid = rotate(grid)
		monsterCount = countMonsters(grid) or countMonsters(grid[::-1])
	print(monsterCount)
	return p1, sum(map(lambda x: x.count("#"), grid))-monsterCount*15