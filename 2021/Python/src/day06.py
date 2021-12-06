from utils.aocUtils import *

def main(input:str):
	fishes = Counter(readNums(input))
	for iter in range(256):
		if iter == 80:
			p1 = sum(fishes.values())
		t = fishes.pop(0,0)
		fishes = Counter({k-1:v for k, v in fishes.items()})+Counter({6:t, 8:t})
	return p1, sum(fishes.values())









def main_old(input:str):
	fishes = defaultdict(int)
	for n in readNums(input):
		fishes[n]+=1
	for _ in range(80):
		fishes = iter(fishes)
	f2 = fishes
	for _ in range(256-80):
		f2 = iter(f2)
	
	return (sum(fishes.values()), sum(f2.values()))