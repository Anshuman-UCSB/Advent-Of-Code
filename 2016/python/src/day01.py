

def main(input:str) -> tuple:
	dir, pos, p2Pos = 1j,0,None
	visited = set()
	for cmd in input.split(", "):
		dir*=-1j if cmd[0] == 'L' else 1j
		for _ in range(int(cmd[1:])):
			pos+=dir
			if(p2Pos == None):
				if(pos in visited):
					p2Pos = pos
				else:
					visited.add(pos)
	
	return (int(abs(pos.real) + abs(pos.imag)),int(abs(p2Pos.real) + abs(p2Pos.imag)))

