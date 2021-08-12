import sys,re
from Queue import PriorityQueue

bots = [map(int, re.findall("-?\d+", line)) for line in sys.stdin]
q = PriorityQueue()
for x,y,z,r in bots:
  d = abs(x) + abs(y) + abs(z)
  q.put((max(0, d - r),1))
  q.put((d + r + 1,-1))
count = 0
maxCount = 0
result = 0
while not q.empty():
  dist,e = q.get()
  count += e
  if count > maxCount:
    result = dist
    maxCount = count
print result