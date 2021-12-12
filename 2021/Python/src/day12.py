from utils.aocUtils import *

p1 = 0
p2 = 0

def BFS(paths, path):
	global p1
	pos = path[-1]
	if(pos == 'end'):
		p1+=1
		return
	for n in paths[pos]:
		if n.islower() and n in path:
			continue
		BFS(paths, path+[n])

def abletorevisit(path):
	c = Counter([p for p in path if p.islower()])
	return all(v<=1 for v in c.values())

def BFS2(paths, path):
	global p2
	pos = path[-1]
	if(pos == 'end'):
		p2+=1
		return
	for n in paths[pos]:
		if n == "start":
			continue
		if not n.islower() or n not in path or abletorevisit(path):
			BFS2(paths, path+[n])

def main(input:str):
	paths = defaultdict(list)
	for l in input.splitlines():
		start, end = l.split('-')
		paths[start].append(end)
		paths[end].append(start)
	BFS(paths, ["start"])
	BFS2(paths, ["start"])
	return (p1, p2)