def dragonCurve(base,size):
	out = base+"0"+"".join(['1' if c == '0' else '0' for c in base[::-1]])
	if len(out) < size:
		return dragonCurve(out, size)
	else:
		return out[:size+1]

def checksum(s):
	next = "".join(['1' if s[i]==s[i+1] else '0' for i in range(0,len(s)-1, 2)])
	if len(next)%2 == 0:
		return checksum(next)
	else: return next

def main(input:str) -> tuple:
	return (checksum(dragonCurve(input, 272)), checksum(dragonCurve(input, 35651584)))
