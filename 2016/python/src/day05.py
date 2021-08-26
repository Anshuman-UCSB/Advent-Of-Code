# from hashlib import md5
from _md5 import md5


def hash(inp):
	return md5(inp.encode()).hexdigest()

def generate(input):
	n = 1
	while True:
		n+=1
		hashed = hash(input+str(n))
		# print(input+str(n))
		if(hashed[:5] == "00000"):
			yield (hashed[5], hashed[6])

def main(input:str) -> tuple:
	
	p1= ""
	p2 = [" " for _ in range(8)]
	g = generate(input)
	for _ in range(8):
		res = next(g)
		p1+=res[0]
		if("0"<=res[0] and res[0]<="7" and p2[int(res[0])]==" "):
			p2[int(res[0])] = res[1]
	while " " in p2:
		res = next(g)
		if("0"<=res[0] and res[0]<="7" and p2[int(res[0])]==" "):
			p2[int(res[0])] = res[1]
	return (p1, "".join(p2))
