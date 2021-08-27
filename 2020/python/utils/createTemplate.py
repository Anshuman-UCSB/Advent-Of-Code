import os
# os.mkdir("src")
for i in range(1,26):
	with open("src/day%02d.py" % (i), 'w') as f:
		f.write(
"""from utils.aocUtils import *
def main(input:str):
	p1 = 0
	p2 = 0
	return (p1, p2)"""
		)