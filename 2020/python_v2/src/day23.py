class Node:
	def __init__(self, val, next=None):
		self.val = val
		self.next= next
	def print(self):
		print(self.val,end=' ')
		t = self.next
		while t != self:
			print(t,end=' ')
			t = t.next
		print()
	def __str__(self):
		return str(self.val)
def decr(n,roll):
	if n>1: return n-1
	return roll
def solve(cups,rounds):
	roll = max(cups)
	ptr = {n:Node(n) for n in cups}
	for i in range(len(cups)):
		ptr[cups[i-1]].next = ptr[cups[i]]
	cur = ptr[cups[0]]
	for r in range(rounds):
		t = cur.next
		cur.next = t.next.next.next
		bad = (t.val, t.next.val, t.next.next.val)
		dest = decr(cur.val,roll)
		while dest in bad:
			dest=decr(dest,roll)
		dest = ptr[dest]
		tmp = dest.next
		dest.next = t
		t.next.next.next = tmp
		cur = cur.next
	return ptr[1]
def main(input):
	cups = list(map(int, input))
	p1 = ""
	p = solve(cups, 100).next
	while p.val!=1:
		p1+=str(p.val)
		p = p.next
	cups = list(map(int, input))+list(range(10,1_000_001))
	p2 = solve(cups, 10_000_000)
	return p1, p2.next.val * p2.next.next.val