from collections import Counter
def main(input):
	tiles = set()
	for l in input.splitlines():
		p = 0
		ns = False
		for c in l:
			match c:
				case 'n':
					p+=1j
					ns = True
				case 's':
					p-=1j
					ns = True
				case 'e':
					p+=2
					if ns:
						p-=1
					ns = False
				case 'w':
					p-=2
					if ns:
						p+=1
					ns = False
		if p in tiles:
			tiles.remove(p)
		else:
			tiles.add(p)
	p1 = len(tiles)
	adj = (2,-2,1j+1,1j-1,-1j+1,-1j-1)
	def getAdj(pos):
		return {pos+a for a in adj}
	for d in range(100):
		consider = set()
		for t in tiles:
			consider.update(getAdj(t)|{t})
		new_tiles = set()
		for t in consider:
			if t in tiles:
				if not(len(getAdj(t)&tiles) in (0,3,4,5,6)):
					new_tiles.add(t)
			else:
				if len(getAdj(t)&tiles) == 2:
					new_tiles.add(t)
		tiles = new_tiles


	return p1, len(tiles)