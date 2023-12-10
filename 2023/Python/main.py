import os
import traceback
import importlib
import argparse
import time
from aocd import get_data, submit

days = [None]+[importlib.import_module(f"src.day{i:02d}") for i in range(1,26)]

parser = argparse.ArgumentParser()
parser.add_argument("day", nargs="?", type=int, help="Select just one day to run")
parser.add_argument("-t", "--test", action="store_true", help="Run tests instead of input")
parser.add_argument("-d", "--debug", action="store_true", help="Include error outputs for test cases")
parser.add_argument("-s", "--submit", action="store_true", help="Submit solutions to AoC")

args = parser.parse_args()
if args.debug:
	args.test = True

	
def runDay(day, path=None):
	path = path or f"data/day{day:02d}/input"
	with open(path,'r+') as f:
		try:
			if f.read() == "":
				f.write(get_data(day=day, year = 2023))
		except Exception:
			return (None, None)
	with open(path,'r') as f:
		inp = f.read().strip()
		start_time = time.time()
		try:
			results = days[day].main(inp)
		except Exception as e:
			if args.debug or not args.test:
				traceback.print_exc()
			results = ("EXCEPTION",None)
		elapsed = time.time() - start_time
		if args.submit and results and path.endswith("input"):
			if results[0]:
				submit(results[0],part='a',day=day, year=2023)
			if results[1]:
				submit(results[1],part='b',day=day, year=2023)
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
		print()

	# with open(f"data/day{day:02d}/input",'r') as f:
	# 	inp = f.read().strip()
	# 	start_time = time.time()
	# 	results = days[day].main(inp)
	# 	elapsed = time.time() - start_time
	# 	return results, elapsed*1000

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
	else:
		printDay(f"Day {args.day}:", *runDay(args.day))