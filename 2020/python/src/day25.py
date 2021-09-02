from utils.aocUtils import *

def transform(subject, loopSize):
	return pow(subject, loopSize+1, 20201227)

def crack1(target):
	i = 0
	t = 7
	while True:
		if t == target:
			return i
		i+=1
		t = modMult(t, 7, 20201227)

def main(input:str):
	target = int(input.splitlines()[0])
	door = int(input.splitlines()[1])
	p1 = transform(door, crack1(target))
	return (p1, None)