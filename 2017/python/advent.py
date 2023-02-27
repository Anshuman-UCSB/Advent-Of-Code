import argparse
import sys
parser = argparse.ArgumentParser()
parser.add_argument("day",help="which day to evaluate, if none is given evaluate all",
					type=int, nargs="?",default=-1,choices=range(1,26))
args = parser.parse_args()

if args.day == -1:
	print("-- ADVENT OF CODE 2017 --")
	for i in range(1,26):
		d = f"day{i}"
		with open(d+'/input','r') as f:
			day=__import__(d+".main")
			fn = eval(f"day.main.day{i}")
			ans=fn(f.read())
			if ans[0]!=None:
				print("Day",i,end=":\n")
				if ans[0]!=None:
					print("[P1]",ans[0])
					if ans[1]!=None:
						print("[P2]",ans[1])
else:
	i=args.day
	d = f"day{i}"
	print("Day",i,end=":\n")
	with open(d+'/input','r') as f:
		day=__import__(d+".main")
		fn = eval(f"day.main.day{i}")
		ans=fn(f.read())
		if ans[0]!=None:
			if ans[0]!=None:
				print("[P1]",ans[0])
				if ans[1]!=None:
					print("[P2]",ans[1])
		else:
			print("ERROR: No output for day")