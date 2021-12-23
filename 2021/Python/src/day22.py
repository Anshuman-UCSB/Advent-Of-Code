from utils.aocUtils import *

def intersection(c1, c2):
	for a, b in zip(c1, c2):
		if a[0] > b[1] or a[1] < b[0]:
			return None
	return tuple((max(a[0], b[0]), min(a[1], b[1])) for a, b, in zip(c1, c2))

def cprint(tup):
	return f"({tup[0][0]},{tup[1][0]},{tup[2][0]})->({tup[0][1]},{tup[1][1]},{tup[2][1]})"

def difference(c1, c2):
	intsc = intersection(c1, c2)
	if not intsc:
		return [c1]
	t = []
	t.append([c1[0],c1[1], (c1[2][0], intsc[2][0]-1)])
	t.append([c1[0],c1[1], (intsc[2][1]+1, c1[2][1])])
	t.append([intsc[0], (c1[1][0], intsc[1][0]-1), intsc[2]])
	t.append([intsc[0], (intsc[1][1]+1, c1[1][1]), intsc[2]])
	t.append([(c1[0][0], intsc[0][0]-1), c1[1], intsc[2]])
	t.append([(intsc[0][1]+1, c1[0][1]), c1[1], intsc[2]])
	return [(x,y,z) for x,y,z in t if x[0]<=x[1] and y[0]<=y[1] and z[0]<=z[1]]

def main(input:str):
	p1 = 0
	p2 = 0
	cubes = []
	for l in input.splitlines():
		on_off, *cube = tuple([l.split()[0]=="on"]+list(chunks(readNums(l),2)))
		new = []
		for c in cubes:
			new.extend(difference(c, cube))
		if on_off:
			new.append(cube)
		cubes = new
	for c in cubes:
		p1+=prod(max(0, min(50,c[i][1])-max(-50,c[i][0])+1) for i in range(3))
		p2+=prod(c[i][1]-c[i][0]+1 for i in range(3))
	return (p1, p2)