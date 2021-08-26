import re
from time import sleep
from random import shuffle

def iter(rules, base):
	nextSet = set()
	for tar, rep in rules:
		for m in re.finditer(tar, base):
			t = base[:m.start(0)]+rep+base[m.end(0):]
			nextSet.add(t)
	return nextSet
def riter(rules, base):
	nextSet = set()
	for rep, tar in rules:
		for m in re.finditer(tar, base):
			t = base[:m.start(0)]+rep+base[m.end(0):]
			nextSet.add(t)
	return nextSet

def p2(rules, base):
	rules.sort(key = lambda x: -len(x[1]))
	
	step = 0
	t = base
	while t != 'e':
		changed = False
		for rep, tar in rules:
			if tar in t:
				t = t.replace(tar,rep,1)
				step+=1
				changed = True
				break
		if changed == False:
			t = base
			step = 0
			shuffle(rules)
	return step
			

def main(input:str) -> tuple:
	nextSet = set()
	base = input.splitlines()[-1]
	rules = []
	for l in input.splitlines()[:-2]:
		tar, _ , rep = l.split()
		rules.append((tar, rep))
	# print(rules)
	p1 = len(iter(rules, base))
	rules.sort(key = lambda x: -len(x[1]))

	return (p1, p2(rules, base))