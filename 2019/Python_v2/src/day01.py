from utils.aocUtils import *

def fuelNeeded(num):
	if(num<=0):
		return 0
	return num//3-2 + fuelNeeded(num//3-2)

def main(input:str):
	nums = list(map(int, input.splitlines()))
	p1 = sum([x//3-2 for x in nums])
	p2 = sum([fuelNeeded(x) for x in nums])
	return (p1, p2)