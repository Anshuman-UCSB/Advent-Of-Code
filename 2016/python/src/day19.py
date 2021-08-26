from collections import deque

def main(input:str) -> tuple:
	q = deque(range(1,int(input)+1))
	while len(q)>1:
		q.rotate(-1)
		q.popleft()
	k = 3
	while k<int(input):
		k*=3
	k/=3
	return (q[0], int(input)-int(k))
