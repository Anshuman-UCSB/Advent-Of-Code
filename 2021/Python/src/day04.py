from utils.aocUtils import *
import re

def isWinner(board, called):
	for i in range(5):
		if set(board[i*5:i*5+5]) <= called or set(board[i::5]) <= called:
			return True
	return False

def score(board, called, n):
	return n*sum(x for x in board if x not in called)

def p1(boards, nums):
	called = set()
	for n in nums:
		called.add(n)
		for b in boards:
			if(isWinner(b, called)):
				return score(b, called, n)
def p2(boards, nums):
	called = set()
	for n in nums:
		called.add(n)
		for b in boards:
			if(isWinner(b, called)):
				if len(boards) == 1:
					return score(b, called, n)
				boards.remove(b)
				
def main(input:str):
	nums = readNums(input.splitlines()[0])
	boards = []
	for board in input.split("\n\n")[1:]:
		b = []
		for n in readNums(board):
			b.append(n)
		boards.append(b)
	return (p1(boards, nums), p2(boards, nums))