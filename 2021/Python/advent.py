#!/usr/bin/pypy
utilSource = "../../Templates/Python/"
YEAR = 2021

import sys, os
import time
sys.path.append(utilSource)

import requests
from src.day01 import main as day01
from src.day02 import main as day02
from src.day03 import main as day03
from src.day04 import main as day04
from src.day05 import main as day05
from src.day06 import main as day06
from src.day07 import main as day07
from src.day08 import main as day08
from src.day09 import main as day09
from src.day10 import main as day10
from src.day11 import main as day11
from src.day12 import main as day12
from src.day13 import main as day13
from src.day14 import main as day14
from src.day15 import main as day15
from src.day16 import main as day16
from src.day17 import main as day17
from src.day18 import main as day18
from src.day19 import main as day19
from src.day20 import main as day20
from src.day21 import main as day21
from src.day22 import main as day22
from src.day23 import main as day23
from src.day24 import main as day24
from src.day25 import main as day25

from utils.aocUtils import *

days = [
	None,
	day01,
	day02,
	day03,
	day04,
	day05,
	day06,
	day07,
	day08,
	day09,
	day10,
	day11,
	day12,
	day13,
	day14,
	day15,
	day16,
	day17,
	day18,
	day19,
	day20,
	day21,
	day22,
	day23,
	day24,
	day25
]

def loadInput(day):
	if os.path.exists(os.path.join("input","day{:0>2}.txt".format(day))):
		return
	year = 2021

	cookie = {"session":"***REMOVED***"}
	r = requests.get(f"https://adventofcode.com/{year}/day/{day}/input", cookies=cookie)
	if not r.text.startswith("Please"):
		with open("input/day{:0>2}.txt".format(day), 'w') as f:
			f.write(r.text)

notYetDay = False

def runDay(day):
	loadInput(day)
	if not os.path.exists(os.path.join("input","day{:0>2}.txt".format(day))):
		global notYetDay
		notYetDay = True
		return 0
	print(f"	DAY {day}: ")
	dayStr = str(day).zfill(2)
	inp = open(f"input/day{dayStr}.txt", "r").read()
	start = time.time_ns()
	res = days[day](inp)
	end = time.time_ns()
	printAnswer(res)
	print("Execution took",round((end-start)/1e6,1),end="ms\n")
	return end-start

if __name__ == "__main__":
	if(len(sys.argv) == 2):
		try:
			runDay(int(sys.argv[1]))
		except FileNotFoundError:
			print("ERROR: invalid argument", sys.argv[1])
	else:
		print(f"Advent of Code {YEAR} [Python]")
		total = 0
		for i in range(1,26):
			total+=runDay(i)
			if notYetDay:
				break
			print()
		print("Total execution time:",round(total/1e6, 1),end="ms\n")