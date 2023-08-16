class Mask:
	def __init__(self, inp):
		self.raw_mask = inp
		self.posMask = int(self.raw_mask.replace('X','0'),2)
		self.negMask = int(self.raw_mask.replace('X','1'),2)
	def apply(self, num):
		return (num & self.negMask) | self.posMask

def apply1(num, pos):
	return num | 1<<pos
def apply0(num, pos):
	return num & (((1<<36)-1) ^ (1<<pos))

class Mask2:
	def __init__(self, inp):
		self.raw_mask = inp
		self.pos_mask = int(inp.replace('X','0'),2)
		self.floaters = [35-i for i,v in enumerate(self.raw_mask) if v == 'X']
	def apply(self, num):
		nums = [num|self.pos_mask]
		for f in self.floaters:
			nums = [apply1(n, f) for n in nums]+[apply0(n, f) for n in nums]
		return nums
def main(input):
	mem1 = {}
	mem2 = {}
	mask = None
	for l in input.splitlines():
		if l.startswith("mask"):
			mask = Mask(l.split()[-1])
			mask2 = Mask2(l.split()[-1])
		elif l.startswith("mem"):
			addr = int(l.replace(']','[').split('[')[1])
			mem1[addr] = mask.apply(int(l.split()[-1]))
			for addr in mask2.apply(addr):
				mem2[addr] = int(l.split()[-1])
	return sum(mem1.values()), sum(mem2.values())