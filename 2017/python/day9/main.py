def day9(input):
	depth = 0
	state = 0
	p1 = 0
	p2 = 0
	# States:
	# 0 - reset
	# 1 - inside
	# 2 - ignore
	i = 0
	while i<len(input):
		if input[i] == '!':
			i+=2
		else:
			if state == 0:
				if input[i] == '{':
					depth+=1
				if input[i] == '}':
					p1+=depth
					# print(depth)
					depth-=1
				if input[i] == '<':
					state = 1
			elif state == 1:
				if input[i] == '>':
					state = 0
				else:
					p2+=1
			i+=1
	return [p1,p2]