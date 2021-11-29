from utils.aocUtils import *

def main(input:str):
	s = 25*6
	layers = []
	t = []
	for c in input:
		t.append(c)
		if len(t) == s:
			layers.append(t)
			t = []
	
	zeros = s
	p1 = 0
	for l in layers:
		c = l.count('0')
		if c < zeros:
			zeros = c
			p1 = l.count('1')*l.count('2')

	picture = ['2'] * s
	for l in layers:
		for i, v in enumerate(l):
			if picture[i] == '2':
				picture[i] = v
	p2 = "\n"
	for i, v, in enumerate(picture):
		p2+=('#' if v == '1' else ' ')
		if i%25==24:
			p2+="\n"
	return (p1, p2)