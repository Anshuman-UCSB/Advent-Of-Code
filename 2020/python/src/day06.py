from utils.aocUtils import *
def main(input:str):
	lines = list(map(lambda x: x.splitlines(), input.split("\n\n")))
	p1 = sum([len(reduce(lambda a, b: a.union(b), map(set, x))) for x in lines])
	p2 = sum([len(reduce(lambda a, b: a.intersection(b), map(set, x))) for x in lines])
	return (p1, p2)