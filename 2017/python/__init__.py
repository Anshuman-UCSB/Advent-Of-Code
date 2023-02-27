template = """
def day{}(input):
	return [None,None]
""".strip()

if __name__ == "__main__":
	import os
	for i in range(1,26):
		try:
			os.mkdir(f"day{i}")
			with open(f"day{i}/main.py",'w') as f:
				f.write(template.format(i))
			open(f"day{i}/input",'w').close()
		except FileExistsError:
			print("Skipping day",i)