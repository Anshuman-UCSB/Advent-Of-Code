
def p1(string):
	weights = [1] * len(string)
	length = 0
	waitUntil = 0
	startCount = -1
	for i in range(len(string)):
		if(string[i] == "(" and i>=waitUntil):
			xLoc = string.find("x", i)
			endLoc = string.find(")", xLoc)
			a = int(string[i+1:xLoc])
			b = int(string[xLoc+1: endLoc])
			for k in range(endLoc+1, endLoc+1+a):
				weights[k]*=b
			waitUntil = endLoc+a+1
			startCount = endLoc
		elif i > startCount:
			length+=weights[i]
	return length

def p2(string):
	weights = [1] * len(string)
	length = 0
	for i in range(len(string)):
		if(string[i] == "("):
			xLoc = string.find("x", i)
			endLoc = string.find(")", xLoc)
			a = int(string[i+1:xLoc])
			b = int(string[xLoc+1: endLoc])
			for k in range(endLoc+1, endLoc+1+a):
				weights[k]*=b
		elif 'A'<=string[i] and string[i]<='Z':
			length+=weights[i]
	return length

def main(input:str) -> tuple:
	return (p1(input), p2(input))
