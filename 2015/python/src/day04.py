from utils.aocUtils import hash

def main(input:str) -> tuple:
	p1 = None
	p2 = 0
	while True:
		p2+=1
		if p1 == None and hash(input+str(p2)).startswith("00000"): p1 = p2
		if hash(input+str(p2)).startswith("000000"):break
	return (p1, p2)