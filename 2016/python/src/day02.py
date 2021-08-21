
def solve(input, map):
	out = ""
	pos = 0
	dirs = {'U':1j, 'R':1, 'D':-1j, 'L':-1}
	for l in input.splitlines():
		for c in l:
			if(pos+dirs[c] in map.keys()):
				pos+=dirs[c]
		out+=map[pos]
	return out

def main(input:str) -> tuple:
	map1 = {
		0:"5",
		1:"6",
		-1:"4",
		0+1j:"2",
		1+1j:"3",
		-1+1j:"1",
		0-1j:"8",
		1-1j:"9",
		-1-1j:"7"
	}
	map2 = {
		2j+2:"1",
		1+1j:"2", 2+1j:"3", 3+1j:"4",
		0:"5",1:"6",2:"7",3:"8",4:"9",
		1-1j:"A", 2-1j:"B", 3-1j:"C",
		-2j+2:"D",
	}
	return (solve(input, map1), solve(input, map2))
