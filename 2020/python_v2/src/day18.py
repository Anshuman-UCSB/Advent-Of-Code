def solve(expr):
	expr = expr.replace("(", "( ").replace(")", " )")
	tokens = expr.split()
	tokens = [int(t) if t.isalnum() else t for t in tokens]
	while True:
		# print(" ".join(map(str,tokens)))
		if ')' not in tokens:
			acc = tokens[0]
			for i in range(2, len(tokens),2):
				if tokens[i-1] == '*':
					acc*=tokens[i]
				else:
					acc+=tokens[i]
			return acc
		close = tokens.index(")")
		open = close
		while tokens[open] != '(':
			open-=1
		acc = tokens[open+1]
		for i in range(open+3, close,2):
			if tokens[i-1] == '*':
				acc*=tokens[i]
			else:
				acc+=tokens[i]
		tokens = tokens[:open]+[acc]+tokens[close+1:]
def solve2(expr):
	expr = expr.replace("(", "( ").replace(")", " )")
	tokens = expr.split()
	tokens = [int(t) if t.isalnum() else t for t in tokens]
	while True:
		# print(" ".join(map(str,tokens)))
		if ')' not in tokens:
			while True:
				change = False
				for i in range(2,len(tokens)):
					if isinstance(tokens[i], int) and tokens[i-1] == '+' and isinstance(tokens[i-2], int):
						tokens[i-2]+=tokens[i]
						del tokens[i-1:i+1]
						change = True
						break
				if change: continue
				for i in range(2,len(tokens)):
					if isinstance(tokens[i], int) and tokens[i-1] == '*' and isinstance(tokens[i-2], int):
						tokens[i-2]*=tokens[i]
						del tokens[i-1:i+1]
						change = True
						break
				if change: continue
				break
			return tokens[0]
		close = tokens.index(")")
		open = close
		while tokens[open] != '(':
			open-=1
		sub = " ".join(map(str, tokens[open+1:close]))
		tokens = tokens[:open]+[solve2(sub)]+tokens[close+1:]

# def solve2(expr):
# 	expr = expr.replace("(", "( ").replace(")", " )")
# 	tokens = expr.split()
# 	tokens = [int(t) if t.isalnum() else t for t in tokens]
# 	while True:
# 		print(tokens)
# 		change = False
# 		for i in range(2,len(tokens)):
# 			if tokens[i] == ')' and isinstance(tokens[i-1], int) and tokens[i-2] == '(':
# 				del tokens[i-2:i+1:2]
# 				change = True
# 				break
# 		if change: continue
# 		for i in range(2,len(tokens)):
# 			if isinstance(tokens[i], int) and tokens[i-1] == '+' and isinstance(tokens[i-2], int):
# 				tokens[i-2]+=tokens[i]
# 				del tokens[i-1:i+1]
# 				change = True
# 				break
# 		if change: continue
# 		for i in range(2,len(tokens)):
# 			if isinstance(tokens[i], int) and tokens[i-1] == '*' and isinstance(tokens[i-2], int):
# 				tokens[i-2]*=tokens[i]
# 				del tokens[i-1:i+1]
# 				change = True
# 				break
# 		if change: continue
# 		break
# 	return tokens[0]

def main(input):
	p1 = 0
	p2 = 0
	for l in input.splitlines():
		p1 += solve(l)
		p2 += solve2(l)
	return p1,p2
# doesn't respect (a+b)*c+4
# def solve(expr):
# 	expr = expr.replace("(", "( ").replace(")", " )")
# 	tokens = expr.split()
# 	tokens = [int(t) if t.isalnum() else t for t in tokens]
# 	while len(tokens)>1:
# 		print(" ".join(map(str, tokens)))
# 		acc = None
# 		op = None
# 		build = []
# 		for t in tokens:
# 			if t == "(":
# 				if acc:
# 					build.extend((acc, op, '('))
# 				elif op:
# 					build.extend((op, '('))
# 				else:
# 					build.append("(")
# 				acc = None
# 				op = None
# 			elif t == ")":
# 				if acc:
# 					build.extend((acc, ')'))
# 				else:
# 					build.append(")")
# 				acc = None
# 				op = None
# 			elif str(t) in "+*":
# 				op = t
# 			else:
# 				assert type(t) is int, t
# 				if acc == None:
# 					acc = t
# 					if op:
# 						build.append(op)
# 				else:
# 					if op == '*':
# 						acc*=t
# 					else:
# 						acc+=t
# 		if acc:
# 			build.append(acc)
# 		p = 0
# 		while p<len(build):
# 			if build[p] == '(' and build[p+2] == ')':
# 				del build[p+2]
# 				del build[p]
# 				p = -1
# 			p+=1
# 		tokens = build
# 	return tokens[0]