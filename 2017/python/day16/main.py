def day16(input):
	x = list("abcdefghijklmnop")
	# x = list("abcde")
	p1=None
	seen = {}
	i=0
	while i<1000000000:
		i+=1
		for cmds in input.split(','):
			if cmds[0]=='s':
				n=int(cmds[1:])
				x=x[-n:]+x[:-n]
			elif cmds[0]=='x':
				a,b=map(int,cmds[1:].split('/'))
				x[a],x[b]=x[b],x[a]
			elif cmds[0]=='p':
				a,b=map(lambda c:x.index(c),cmds[1:].split('/'))
				x[a],x[b]=x[b],x[a]
		s="".join(x)
		if p1==None:
			p1=s
		if s in seen:
			cycle=i-seen[s]
			i+=((1000000000-i)//cycle)*cycle
			seen={}
		seen[s]=i
		# print(x)
	return [p1,s]