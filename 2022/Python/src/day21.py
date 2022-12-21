from operator import add, sub, mul, truediv
ops = {'+':add,'-':sub,'*':mul,'/':truediv}

class Node:
	def __init__(self, l):
		self.name = l[:4]
		self.raw = l[6:]
		self.val = None
	def eval(self):
		if self.val is None:
			return self.op(self.lhs.eval(), self.rhs.eval())
		else:
			return self.val
def buildTree(nodes, node='root'):
	n = nodes[node]
	raw = n.raw
	if raw[0] in "0123456789":
		n.val = int(raw)
	else:
		lhs, op, rhs = raw.split()
		n.lhs = nodes[lhs]
		n.rhs = nodes[rhs]
		n.op = ops[op]
		for t in (lhs,rhs):
			buildTree(nodes, t)

def main(input:str):
	nodes = {}
	for l in input.splitlines():
		n = Node(l)
		nodes[n.name] = n
	buildTree(nodes, "root")
	root = nodes['root']
	p1 = int(root.eval())

	nodes['humn'].val = 1j
	solve, const = root.lhs.eval(), root.rhs.eval()
	if const.imag:
		solve,const = const,solve
	p2 = int((const-solve.real)/solve.imag)
	
	return (p1, p2)