class Node:
	def __init__(self, val, next=None, prev = None):
		self.val = val
		self.next = next
		self.prev = prev
	
class llist:
	def append(self, val):
		self.size+=1
		if self.head == None:
			self.head = Node(val)
			self.tail = self.head
		else:
			self.tail.next = Node(val, prev = self.tail)
			self.tail = self.tail.next
	
	def appendLeft(self, val):
		self.size+=1
		if self.head == None:
			self.head = Node(val)
			self.tail = self.head
		else:
			v = Node(val, self.head)
			self.head.prev = v
			self.head = v

	def insert(self, node, val):
		v = Node(val, self.head.next, self.head)
		self.head.next.prev = v
		self.head.next = v
		self.size+=1

	def __init__(self, initList = None):
		if initList == None:
			initList = []
		self.size = 0
		self.head = None
		self.tail = None