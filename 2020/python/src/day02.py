from utils.aocUtils import *
import re
def main(input:str):
	p1 = 0
	p2 = 0
	for l in input.splitlines():
		spl = re.split("[- :]+", l)
		if int(spl[0])<=spl[-1].count(spl[-2])<=int(spl[1]):
			p1+=1
		if (spl[-1][int(spl[0])-1] == spl[2]) != (spl[-1][int(spl[1])-1] == spl[2]):
			p2+=1
	return (p1, p2)