from utils.aocUtils import *
def main(input:str):
	p1 = p2 = 0
	for i in range(4,len(input)):
		if p1 == 0 and len(set(input[i-4:i])) == 4:
			p1 = i
		if len(set(input[i-14:i])) == 14:
			p2 = i
			break
	return (p1, p2)