from utils.aocUtils import *

def eval1(eq):
	# print("EVAL:",eq)
	if '(' not in eq:
		spl = eq.split(" ")
		stack = []
		ops = []
		for s in spl:
			# print(s, stack, ops)
			if s not in ['+', '*']:
				if ops == []:
					stack.append(int(s))
				else:
					op = ops.pop()
					if op == '*':
						stack[-1]*=int(s)
					else:
						stack[-1]+=int(s)
			else:
				ops.append(s)
		return stack[0]
	else:
		levels = [""]
		for c in eq:
			if c == '(':
				levels.append('')
			elif c == ')':
				t = str(eval1(levels.pop()))
				levels[-1]+=t
			else:
				levels[-1]+=c
		return eval1(levels[0])

def eval2(eq):
	# print("EVAL:",eq)
	if '(' not in eq:
		spl = eq.split(" ")
		stack = []
		ops = []
		for c in stack:
			if c == '*':
				ops.append('*')
			else:
				if ops == []:
					stack.append(c)
	else:
		levels = [""]
		for c in eq:
			if c == '(':
				levels.append('')
			elif c == ')':
				t = str(eval2(levels.pop()))
				levels[-1]+=t
			else:
				levels[-1]+=c
		return eval2(levels[0])

def main(input:str):
	p1 = sum([eval1(l) for l in input.splitlines()])
	p2 = 0
	return (p1, p2)