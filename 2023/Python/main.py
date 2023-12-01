import os
import importlib
import argparse
import time

days = [None]+[importlib.import_module(f"src.day{i:02d}") for i in range(1,26)]

parser = argparse.ArgumentParser()
parser.add_argument("day", nargs="?", type=int, help="Select just one day to run")
parser.add_argument("-t", "--test", action="store_true", help="Run tests")

def runDay(day, path=None):
	path = path or f"data/day{day:02d}/input"
	with open(path,'r') as f:
		inp = f.read()
		start_time = time.time()
		results = days[day].main(inp)
		elapsed = time.time() - start_time
		return results, elapsed*1000

def printDay(intro, results, elapsed):
	print(intro)
	if results == None:
		print("  No output")
	else:
		print("  Part 1:",results[0])
		if results[1] != None:
			print("  Part 2:",results[1])
		print(f"  took {int(elapsed)}ms")

def runTests(day):
	test_paths = os.listdir(f"data/day{day:02d}/tests")
	for test_path in test_paths:
		printDay(f"Test {test_path}:", *runDay(day, f"data/day{day:02d}/tests/"+test_path))

	with open(f"data/day{day:02d}/input",'r') as f:
		inp = f.read()
		start_time = time.time()
		results = days[day].main(inp)
		elapsed = time.time() - start_time
		return results, elapsed*1000

args = parser.parse_args()
if args.day == None:
	print(" -- ADVENT OF CODE 2023 --")
	if args.test: print("(test flag ignored due to running all days)")
	print()
	total = 0
	for i in range(1,26):
		results, elapsed = runDay(i)
		if results == None: break
		printDay(f"Day {i}:", results, elapsed)
		total+=elapsed
	print(f"\nAll days combined took {int(total)}ms")
else:
	if args.test:
		runTests(args.day)
	printDay(f"Day {args.day}:", *runDay(args.day))