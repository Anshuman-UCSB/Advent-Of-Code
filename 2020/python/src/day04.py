from utils.aocUtils import *
import re
def p1f(n):
	for req in ["byr","iyr","eyr","hgt","hcl","ecl","pid"]:
		if req not in n:
			return False
	return True

def byr(s):
	try:
		return 1920<=int(re.findall(r".*byr:(\d{4})\s", s)[0])<=2002
	except IndexError:
		return False
def iyr(s):
	try:
		return 2010<=int(re.findall(r".*iyr:(\d{4})\s", s)[0])<=2020
	except IndexError:
		return False
def eyr(s):
	try:
		return 2020<=int(re.findall(r".*eyr:(\d{4})\s", s)[0])<=2030
	except IndexError:
		return False

def hgt(s):
	try:
		m = re.findall(r"hgt:(\d+)(cm|in)\s",s)[0]
		if m[1] == 'cm':
			return 150<=int(m[0])<=193
		else:
			return 59<=int(m[0])<=76		
	except IndexError:
		return False

def hcl(s):
	try:
		m = re.findall(r"hcl:#[0-9a-f]{6}\s",s)[0]
		return True
	except IndexError:
		return False
def ecl(s):
	try:
		m = re.findall(r"ecl:(amb|blu|brn|gry|grn|hzl|oth)\s",s)[0]
		return True
	except IndexError:
		return False
def pid(s):
	try:
		m = re.findall(r"pid:\d{9}\s",s)[0]
		return True
	except IndexError:
		return False

def p2f(s):
	for f in [byr, iyr, eyr, hgt, hcl, ecl, pid]:
		if not f(s+" "):
			return False
	return True

def main(input:str):
	lines = input.split("\n\n")
	p1 = len(list(filter(p1f, lines)))
	p2 = len(list(filter(p2f, lines)))
	
	return (p1, p2)