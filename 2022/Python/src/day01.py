from utils.aocUtils import *
def main(input:str):
	elves = [sum(map(int,i.splitlines())) for i in input.split("\n\n")]
	elves.sort()
	return (max(elves),sum(elves[-3:]))