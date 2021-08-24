from src.aocUtils import readNums

ranges = []

def merge(ranges):
	ranges.sort()
	for i in range(len(ranges)-1,0,-1):
		if(ranges[i-1][1]+1>=ranges[i][0]):
			ranges[i-1][1] = max(ranges[i-1][1],ranges[i][1])
			ranges[i-1][0] = min(ranges[i-1][0],ranges[i][0])
			del ranges[i]

def main(input:str) -> tuple:
	for r in input.splitlines():
		ranges.append(list(map(int, r.split("-"))))
	old = 0
	while old != len(ranges):
		old = len(ranges)
		merge(ranges)
	p2 = 4294967296
	for low,high in ranges:
		p2-=(high-low+1)

	return (ranges[0][1]+1, p2)
