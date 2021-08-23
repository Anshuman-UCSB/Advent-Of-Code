from src.aocUtils import imaginaryCoordToTuple
from src.grid import GridType

favNum = 0

def isWall(x, y):
	if x<0 or y<0: return True
	value = x * x + 3 * x + 2 * x * y + y + y * y + 1352
	one_bits = bin(value).count('1')
	return one_bits % 2 == 1 

class grid(GridType):
	def at(self, crd) -> bool:
		return isWall(crd[0], crd[1])

def main(input:str) -> tuple:
	global favNum
	favNum = int(input)
	g = grid()
	return (g.bfs((1,1), (31,39))[0], g.getReachable((1,1), 50))