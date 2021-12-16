from utils.aocUtils import *
p1 = 0

def parse(inp):
	global p1
	V, T, content = inp[0:3], inp[3:6], inp[6:]
	p1+=int(V, 2)
	if T == "100": # literal
		i = 0
		val = ""
		while True:
			val+=content[i+1:i+5]
			if content[i] == '0':
				break
			i+=5
		val = int(val, 2)
		return val, inp[i+11:]
	else:
		if content[0] == '0':
			length = int(content[1:16],2)
			spRaw = content[16:16+length]
			rest = content[16+length:]
			subpackets = []
			while spRaw:
				subpackets.append(None)
				subpackets[-1], spRaw = parse(spRaw)
		if content[0] == '1':
			count = int(content[1:12],2)
			spRaw = content[12:]
			subpackets = []
			for _ in range(count):
				subpackets.append(None)
				subpackets[-1], spRaw = parse(spRaw)
			rest = spRaw
		match T:
			case "000":
				subpackets = sum(subpackets)
			case "001":
				subpackets = prod(subpackets)
			case "010":
				subpackets = min(subpackets)
			case "011":
				subpackets = max(subpackets)
			case "101":
				subpackets = 1 if subpackets[0] > subpackets[1] else 0
			case "110":
				subpackets = 1 if subpackets[0] < subpackets[1] else 0
			case "111":
				subpackets = 1 if subpackets[0] == subpackets[1] else 0
		return subpackets, rest
def main(input:str):
	p2 = 0
	l = len(input)*4
	binary = (bin(int(input, 16))[2:]).zfill(l)
	
	p2 = parse(binary)[0]

	return (p1, p2)