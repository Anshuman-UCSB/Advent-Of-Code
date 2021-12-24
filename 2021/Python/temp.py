def eq(a, b):
	return 1 if a==b else 0
def test(inp):
	x = y = z = w = 0
	inputQ = [int(x) for x in inp]
	assert(len(inputQ) == 14)
	w = inputQ.pop(0)
	x = 0
	x+=z
	x%=26
	x+=13
	x = eq(x, w)
	x = eq(x,0)
	y=0
	y=25
	y*=x
	#line 12
	y+=1
	z*=y
	y=0
	