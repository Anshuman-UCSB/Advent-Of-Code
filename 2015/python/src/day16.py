from utils.aocUtils import readNums

def p1Match(sue, needle):
	for k, v in sue.items():
		if needle[k] != v:
			return False
	return True

def p2Match(sue, needle):
	for k, v in sue.items():
		if k in ["cats", "trees"]:
			if needle[k] >= v:
				return False
		elif k in ["pomeranians", "goldfish"]:
			if needle[k] <= v:
				return False
		else:
			if needle[k] != v:
				return False
			
	return True


def main(input:str) -> tuple:
	needle = {
		"children": 3,
		"cats": 7,
		"samoyeds": 2,
		"pomeranians": 3,
		"akitas": 0,
		"vizslas": 0,
		"goldfish": 5,
		"trees": 3,
		"cars": 2,
		"perfumes": 1
	}

	for l in input.splitlines():
		spl = l.split()
		nums = readNums(l)
		sue = {spl[2][:-1]:nums[1], spl[4][:-1]:nums[2], spl[-2][:-1]:nums[-1]}
		if p1Match(sue, needle):
			p1 = nums[0]
		if p2Match(sue, needle):
			p2 = nums[0]
		

	return (p1, p2)