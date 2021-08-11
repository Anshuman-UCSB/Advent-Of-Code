from collections import *
import itertools
import random
import sys
import re

f = open("Day 20/input").read().strip("\n")

d = {
    "N": (0, -1),
    "E": (1, 0),
    "S": (0, 1),
    "W": (-1, 0)
}

positions = []
x, y = 5000, 5000
m = defaultdict(set)
prev_x, prev_y = x, y
distances = defaultdict(int)
dist = 0
for c in f[1:-1]:
    print(c, len(positions))
    if c == "(":
        positions.append((x, y))
    elif c == ")":
        x, y = positions.pop()
    elif c == "|":
        x, y = positions[-1]
    else:
        dx, dy = d[c]
        x += dx
        y += dy
        m[(x, y)].add((prev_x, prev_y))
        if distances[(x, y)] != 0:
            distances[(x, y)] = min(distances[(x, y)], distances[(prev_x, prev_y)]+1)
        else:
            distances[(x, y)] = distances[(prev_x, prev_y)]+1
        
        
    


    prev_x, prev_y = x, y

print(max(distances.values()))
print(len([x for x in distances.values() if x >= 0]))