import heapq

class Heap:
	def __init__(self, iterable = None):
		self.h = []
		if iterable:
			for v in iterable:
				heapq.heappush(self.h, v)
	
	def push(self, val):
		heapq.heappush(self.h, val)
	
	def pop(self):
		return heapq.heappop(self.h)
	
	def __bool__(self):
		return len(self.h)>0