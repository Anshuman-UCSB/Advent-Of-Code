from utils.aocUtils import factors

def p1(target):
	i = 1
	while True:
		c = sum(factors(i))*10
		if c >= target:
			return i
		i+=1
	return i

def p2(target):
	i = 1
	while True:
		c = sum(filter(lambda x: i<=x*50, factors(i)))*11
		if c >= target:
			return i
		i+=1
	return i

def main(input:str) -> tuple:
	return (p1(int(input)), p2(int(input)))