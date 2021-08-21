import regex as re

def supportsTLS(line):
	spl = re.split('\[|\]', line)
	abba = r"([a-z])([a-z])\2\1"
	flag = False
	for i in range(1,len(spl), 2):
		match = re.search(abba, spl[i])
		if(match and match.group()[0] != match.group()[1]):
			return False
	for i in range(0,len(spl), 2):
		match = re.search(abba, spl[i])
		if(match and match.group()[0] != match.group()[1]):
			flag = True
	return flag

def supportsSSL(line):
	spl = re.split('\[|\]', line)
	aba = r"([a-z])([a-z])\1"
	outer = spl[::2]
	inner = spl[1::2]
	for l in outer:
		for m in re.findall(aba, l, overlapped = True):
			# print(m)
			if(m[0] != m[1]):
				for inners in inner:
					if(f"{m[1]}{m[0]}{m[1]}" in inners):
						# print("Found in inner", inners)
						return True

	return False

def main(input:str) -> tuple:
	p1 = 0
	p2 = 0
	for l in input.splitlines():
		p1 +=supportsTLS(l)
		p2 +=supportsSSL(l)
	return (p1, p2)
