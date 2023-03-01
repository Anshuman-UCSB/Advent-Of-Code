#!/usr/bin/env pypy
import os
import argparse
import sys
from time import perf_counter

sys.dont_write_bytecode = True
parser = argparse.ArgumentParser()
parser.add_argument("day",help="Which day to evaluate, if not given evaluate all",
					type=int, nargs="?",default=-1,choices=range(1,26))
parser.add_argument("--test",'-t',help="If used will run output across each testcase (only for individual day)",
					action='store_true')
parser.add_argument("--debug",'-d',help="Run test cases but don't run input",
					action='store_true')
parser.add_argument("--case",'-c',help="Run on a specific test case and output everything (only for individual day)",
					type=int, default=False)


args=parser.parse_args()
def evalDay(i, isTest):
	d = f"day{i}"
	elapsed = 0
	day=__import__(d+".main")
	fn = eval(f"day.main.day{i}")
	if isTest == False:
		with open(d+'/input','r') as f:
			start = perf_counter()
			ans=fn(f.read())
			elapsed = (perf_counter()-start)*1000
			if ans[0]!=None:
				print("Day",i,end=":\n")
				if ans[0]!=None:
					print("[P1]",ans[0])
					if ans[1]!=None:
						print("[P2]",ans[1])
				print(f"Took {elapsed:.3f}ms")
			else:
				elapsed=0
	else:
		print("Day",i,end=":\n")
		found=False
		for case in sorted([f for f in os.listdir(d) if f.startswith('tc')], key=lambda x: int(x[2:])):
			found=True
			n = int(case[2:])
			with open(f"{d}/tc{n}",'r') as tc:
				print(f"TEST CASE {n} - ",end='')
				try:
					print(fn(tc.read()))
				except Exception as e:
					print("ERROR:",e)
		if not found:
			print("ERROR: No test cases found, test case should be in format \"tc[num]\"")
		if args.debug == False:
			with open(d+'/input','r') as f:
				print(f"INPUT \t    - ",end='')
				try:
					print(fn(f.read()))
				except Exception as e:
					print("ERROR:",e)
						
	return elapsed
if args.day == -1:
	print("-- ADVENT OF CODE 2017 --")
	total=0
	for i in range(1,26):
		total+=evalDay(i,False)
	print(f"\nTotal time: {total:.3f}ms")
else:			
	i=args.day
	if args.case:
		day=__import__(f"day{i}.main")
		fn = eval(f"day.main.day{i}")
		with open(f'day{i}/tc{args.case}','r') as tc:
			print(fn(tc.read()))
	else:
		evalDay(i,args.test or args.debug)