from utils.aocUtils import *
import re

def isWinner(board, called):
	for i in range(5):
		if set(board[i:i+4]).issubset(called):
			return True
		if set(board[i::5]).issubset(called):
			return True
	return False

def score(board, called, n):
	s = 0
	for i in board:
		if i not in called:
			s+=i
	return n*s

def p1(input):
	called = set()
	nums = readNums(input.splitlines()[0])
	boards = []
	for board in input.split("\n\n")[1:]:
		b = []
		for n in readNums(board):
			b.append(n)
		# print(b)
		boards.append(b)
	for n in nums:
		called.add(n)
		for b in boards:
			if(isWinner(b, called)):
				return score(b, called, n)
def p2(input):
	called = set()
	nums = readNums(input.splitlines()[0])
	boards = []
	for board in input.split("\n\n")[1:]:
		b = []
		for n in readNums(board):
			b.append(n)
		boards.append(b)
	for n in nums:
		called.add(n)
		for b in boards:
			if(isWinner(b, called)):
				if len(boards) == 1:
					return score(b, called, n)
				boards.remove(b)
				

def main(input:str):
	return (p1(input), p2(input))