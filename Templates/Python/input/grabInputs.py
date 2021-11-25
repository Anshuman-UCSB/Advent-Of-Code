import requests as re

year = 2019

cookie = {"session":"***REMOVED***"}
for i in range(1,26):
	with open("day{:0>2}.txt".format(i), 'w') as f:
		r = re.get(f"https://adventofcode.com/{year}/day/{i}/input", cookies=cookie)
		f.write(r.text)