from utils.aocUtils import *

def winner(board):
	return any([sum(r)==-5 for r in board]) or any([sum(c)==-5 for c in zip(*board)])

def mark(board, n):
	return [[t if t != n else -1 for t in row] for row in board]

def score(board, n):
	return sum([x for row in board for x in row if x != -1])*n

def main(input:str):
	nums = readNums(input.splitlines()[0])
	raw = input.split('\n\n')[1:]
	boards = []
	for l in raw:
		boards.append([])
		for r in l.splitlines():
			boards[-1].append(readNums(r))

	winners = []
	for n in nums:
		boards = [mark(b, n) for b in boards]
		winners.extend([score(b, n) for b in boards if winner(b)])
		boards = [b for b in boards if winner(b) == False]
	p1 = winners[0]
	p2 = winners[-1]
	return (p1, p2)














	



"""
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
			if(isWinner(b, called) and len(boards)>1):
				boards.remove(b)
		if len(boards) == 1:
			if isWinner(boards[0], called):
				return score(boards[0], called, n)

				
def main(input:str):
	nums = readNums(input.splitlines()[0])
	boards = []
	for board in input.split("\n\n")[1:]:
		b = []
		for n in readNums(board):
			b.append(n)
		boards.append(b)
	return (p1(boards, nums), p2(boards, nums))
"""