from utils.aocUtils import *
from z3 import *
def main(input:str):
	p1 = p2 = 0
	d = IntVector('d', 14)
	mx, mn = Optimize(), Optimize()
	criterias = []
	for i in range(14):
		criterias.append(0<d[i])
		criterias.append(d[i]<=9)
	criterias.append(d[0]+6-6==d[13])
	criterias.append(d[1]+11-6==d[12])
	criterias.append(d[2]+5-13==d[11])
	criterias.append(d[3]+6-8==d[8])
	criterias.append(d[4]+8-1==d[5])
	criterias.append(d[6]+9-16==d[7])
	criterias.append(d[9]+13-16==d[10])
	for c in criterias:
		mx.add(c)
		mn.add(c)
	f = 0
	for i in range(14):
		f = f*10+d[i]
	mnAns = mn.minimize(f)
	mxAns = mx.maximize(f)
	assert(mx.check() and mn.check())
	p1 = mxAns.value()
	p2 = mnAns.value()
	
	return (p1, p2)