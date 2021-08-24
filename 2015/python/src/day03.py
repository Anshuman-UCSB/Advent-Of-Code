def getVisits(path):
	delt = {'^':1j, '>':1, 'v':-1j, '<':-1}
	pos = 0
	visited = set([0])
	for c in path:
		pos+=delt[c]
		visited.add(pos)
	return visited

def main(input:str) -> tuple:
	return (len(getVisits(input)), len(getVisits(input[::2]).union(getVisits(input[1::2]))))