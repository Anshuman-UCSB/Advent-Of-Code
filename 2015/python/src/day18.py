from utils.gol import GameOfLife

class gol18(GameOfLife):
	def inBound(self, coord):
		return 0<=coord[0]<100 and 0<=coord[1]<100

class gol18_2(gol18):
	def iter(self):
		for corner in [(0,0), (99,99),(0,99),(99,0)]:
			self.state.add(corner)
		super().iter()
		for corner in [(0,0), (99,99),(0,99),(99,0)]:
			self.state.add(corner)

def main(input:str) -> tuple:
	g = gol18(input)
	g2 = gol18_2(input)
	for _ in range(100):
		g.iter()
		g2.iter()
	
	return (g.score(), g2.score())