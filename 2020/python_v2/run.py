#!/usr/bin/pypy
import os
import sys
import time

def time_ms():
	return int(round(time.time() * 1000))


funcs = []
try:
	for day in range(1,26):
		funcs.append(__import__(f'src.day{day}',fromlist=[None]))
except ModuleNotFoundError:
	print("Loaded up to day",len(funcs))

def runDay(day, test = False):
	if day > len(funcs):
		print(f"ERROR: Day {day} was unable to be loaded")
		return False
	fn = funcs[day-1].main
	if test == True:
		testDir = f"tests/day{day}"
		for f in os.listdir(testDir):
			print(f"{f}:\t{fn(open(os.path.join(testDir, f),'r').read())}")
	with open(f"input/day{day}",'r') as inp:
		print("=== DAY",day,"===")
		before = time_ms()
		ans = fn(inp.read())
		after = time_ms()

		if type(ans) == tuple:
			print("Part 1:", ans[0])
			print("Part 2:", ans[1])
		else:
			print("Part 1:", ans)
		print("time elapsed:", after-before,"ms")


# runDay(1,test=True)
runDay(1,test="test" in sys.argv)