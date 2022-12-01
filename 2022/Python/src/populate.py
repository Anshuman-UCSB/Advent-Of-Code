source = """from utils.aocUtils import *
def main(input:str):
	p1 = p2 = 0
	return (p1, p2)"""

for i in range(1,26):
	with open(f"day{i:02d}.py",'w') as f:
		f.write(source)