from utils.aocUtils import *
def main(input:str):
	counter = [0 for _ in input.splitlines()[0]]
	for l in input.splitlines():
		for i, c in enumerate(l):
			counter[i]+=1 if c == '1' else -1
	opp = ["1" if x < 0 else "0" for x in counter]
	counter = ["1" if x >= 0 else "0" for x in counter]
	p1 = int("".join(counter),2)*int("".join(opp),2)

	oxy = co2 = input.splitlines()
	for i in range(len(oxy[0])):
		common = 0
		for l in oxy:
			common+= 1 if l[i]=='1' else -1
		oxy = [o for o in oxy if o[i] == ('1' if common>=0 else '0')]
		if(len(oxy) == 1):
			break
	for i in range(len(co2[0])):
		common = 0
		for l in co2:
			common+= 1 if l[i]=='1' else -1
		co2 = [o for o in co2 if o[i] == ('1' if common<0 else '0')]
		if(len(co2) == 1):
			break
	
	p2 = int(oxy[0],2)* int(co2[0],2)
	return (p1, p2)