from utils.aocUtils import readNums
from collections import Counter

def powerset(seq):
    if len(seq) <= 1:
        yield seq
        yield []
    else:
        for item in powerset(seq[1:]):
            yield [seq[0]]+item
            yield item

def main(input:str) -> tuple:
	nums = readNums(input)
	possibles = [x for x in powerset(nums) if sum(x) == 150]
	lengths = list(map(len, possibles))
	c = Counter(lengths)
	p2, cnt = 10000,0
	for k, v in c.items():
		if k<p2:
			p2 = k
			cnt = v
	return (len(possibles), cnt)