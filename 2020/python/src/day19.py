from utils.aocUtils import *
import re

def buildRules(input, p2 = False):
	rules = {}
	done = False
	while not done:
		done = True
		for l in input.split("\n\n")[0].splitlines():
			spl = l.split(": ")

			if "\"" in l and int(spl[0]) not in rules:
				done = False
				rules[int(spl[0])] = spl[1][1]

			if int(spl[0]) in rules:
				continue

			solveable = True
			for n in readNums(spl[1]):
				if n not in rules:
					solveable = False
			if solveable:
				done = False
				rules[int(spl[0])] = "("
				chars = spl[1].split(" ")
				if int(spl[0]) == 11 and p2:
					chars = ["42", "31", "|", "42", "42", "31", "31", "|","42", "42", "42", "31", "31", "31", "|", "42", "42", "42", "42", "31", "31", "31", "31", "|", "42", "42", "42", "42", "42", "31", "31", "31", "31", "31"]
				for c in chars:
					if c != '|':
						rules[int(spl[0])]+=rules[int(c)]
					else:
						rules[int(spl[0])]+="|"
				rules[int(spl[0])]+=")"
				if p2:
					if int(spl[0]) == 8:
						rules[int(spl[0])]+="+"
	return rules

def main(input:str):
	
	rules = buildRules(input)
	p1 = 0
	for l in input.split("\n\n")[1].splitlines():
		if re.match(rules[0]+"$", l):
			p1+=1
			
	p2 = 0
	rules = buildRules(input, True)
	for l in input.split("\n\n")[1].splitlines():
		if re.match(rules[0]+"$", l):
			p2+=1
	return (p1, p2)