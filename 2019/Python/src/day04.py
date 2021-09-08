from utils.aocUtils import *
import re

def nonDecreasing(digits):
	for i in range(len(digits)-1):
		if digits[i+1]<digits[i]: return False
	return True

def hasDuplicate(digits):
	for i in range(len(digits)-1):
		if digits[i+1]==digits[i]: return True
	return False

def hasDuplicate2(digits):
	digits.append(None)
	for i in range(len(digits)-2):
		if digits[i+1]==digits[i] and digits[i]!=digits[i+2] and digits[i]!=digits[i-1]: return True
	return False

def main(input:str):
	low, high = map(int, input.split("-"))
	p1 = 0
	p2 = 0
	for i in range(low, high):
		digits = list(map(int,list(str(i))))
		if nonDecreasing(digits) and hasDuplicate(digits):
			p1+=1
		if nonDecreasing(digits) and hasDuplicate2(digits):
			p2+=1
	return (p1, p2)