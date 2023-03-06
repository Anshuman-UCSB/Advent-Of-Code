def knot(s):
	*nums,=range(256)
	pos = 0
	ss=0
	def wrap(n):
		return n%256
	swaps = [ord(c) for c in s]+[17, 31, 73, 47, 23]
	*nums,=range(256)
	pos = 0
	ss=0
	
	for l in swaps*64:
		for i in range(l//2):
			nums[wrap(pos+i)],nums[wrap(pos+l-i-1)]=nums[wrap(pos+l-i-1)],nums[wrap(pos+i)]
		pos=wrap(pos+l+ss)
		ss+=1
	p2=""
	for i in range(0,256,16):
		v = 0
		for j in range(16):
			v^=nums[i+j]
		p2+=(hex(v)[2:]).zfill(2)
	return p2

def day14(input):
	grid = []
	for i in range(128):
		grid.append([])
		for c in knot(input+"-"+str(i)):
			grid[-1]+=[c for c in bin(int(c,16))[2:].zfill(4)]
		grid[-1] = "".join(map(lambda c: "#" if c=='1' else '.',grid[-1]))
	p1 = 0
	G = set()
	for y,r in enumerate(grid):
		for x,v in enumerate(r):
			if v == '#':
				G.add(x+1j*y)
	p1 = len(G)
	p2 = 0
	q=[]
	dirs = [1,-1,1j,-1j]
	def clean(p):
		if p in G:
			G.remove(p)
		for n in dirs:
			if p+n in G:
				clean(p+n)
	while G:
		p2+=1
		p = G.pop()
		clean(p)

	return [p1,p2]