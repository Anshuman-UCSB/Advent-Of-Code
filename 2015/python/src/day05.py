from collections import Counter
import re
def p1Validate(s):
	for fail in ["ab", "cd", "pq", "xy"]:
		if fail in s: return False
	vowels = 0
	for c in s:
		if c in "aeiou":
			vowels+=1
			if vowels >=3: break
	if vowels<3: return False
	return not not re.search(r"(\w)\1", s)
def p2Validate(s):
	return (not not re.search(r"(\w{2}).*\1", s)) and (not not re.search(r"(\w)\w\1", s))

def main(input:str) -> tuple:
	
	return (sum([p1Validate(s) for s in input.splitlines()]), sum([p2Validate(s) for s in input.splitlines()]))