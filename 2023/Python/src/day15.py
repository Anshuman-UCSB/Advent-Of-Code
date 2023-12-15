def H(inp):
	v = 0
	for c in inp:
		v += ord(c)
		v *= 17
		v %= 256
	return v

def main(input):
	boxes = [[] for _ in range(256)]

	p1 = 0
	for t in input.split(","):
		p1 += H(t)
		if "-" in t:
			label = t[:-1]
			boxes[H(label)] = [l for l in boxes[H(label)] if l[0] != label]
		else:
			label,level = t.split('=')
			target = boxes[H(label)]
			replaced = False
			for l in target:
				if l[0] == label:
					l[1] = int(level)
					replaced = True
			if not replaced:
				target.append([label, int(level)])

	p2 = 0
	for n, b in enumerate(boxes):
		for s, (_, l) in enumerate(b):
			p2 += (n+1) * (s+1) * l
	return p1, p2