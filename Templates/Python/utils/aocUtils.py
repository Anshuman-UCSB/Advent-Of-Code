import re
from functools import reduce
from _md5 import md5
from operator import mul
from math import sqrt
from utils.disjointset import *
from utils.gol import *
from utils.grid import *
from utils.llist import *

def chunks(lst, n):
    """Yield successive n-sized chunks from lst."""
    for i in range(0, len(lst), n):
        yield lst[i:i + n]

def hash(inp):
	return md5(inp.encode()).hexdigest()

def printAnswer(result : tuple):
	print("[P1]",result[0])
	print("[P2]",result[1])

def deltas(iter):
    return [iter[n]-iter[n-1] for n in range(1,len(iter))]

def prod(iter):
    return reduce(mul, iter)

def imaginaryCoordToDist(n: complex):
	return int(abs(n.real)) + int(abs(n.imag))
	
def imaginaryCoordToTuple(n: complex):
	return (int((n.real)) , int((n.imag)))

def readNums(inp):
	return list(map(int, re.findall(r"(-?\d+)", inp)))

def powerset(seq):
    if len(seq) <= 1:
        yield seq
        yield []
    else:
        for item in powerset(seq[1:]):
            yield [seq[0]]+item
            yield item

def gcd(x, y):
   while(y):
       x, y = y, x % y
   return x

def lcm(x, y):
   lcm = (x*y)//gcd(x,y)
   return lcm

def modMult(a, b, mod):
    res = 0
    a = a%mod
    while b:
        if b&1:
            res = (res+a)%mod
        a = (a*2)%mod
        b>>=1
    return res

def factors(n):
        step = 2 if n%2 else 1
        return set(reduce(list.__add__,
                    ([i, n//i] for i in range(1, int(sqrt(n))+1, step) if not n % i)))

#x = a1 mod n1
#x = a2 mod n2
def chinese_remainder(n, a):
    sum=0
    prod=reduce(lambda a, b: a*b, n)
    for n_i, a_i in zip(n,a):
        p=prod//n_i
        sum += a_i* mul_inv(p, n_i)*p
    return sum % prod

def mul_inv(a, b):
    b0= b
    x0, x1= 0,1
    if b== 1: return 1
    while a>1 :
        q=a// b
        a, b= b, a%b
        x0, x1=x1 -q *x0, x0
    if x1<0 : x1+= b0
    return x1


def printSet(toColor, point = "#", space = ' '):
	lx = hx = ly = hy = 0
	for p in toColor:
		x, y = imaginaryCoordToTuple(p)
		lx = min(lx, x-1)
		ly = min(ly, y)
		hx = max(hx, x+1)
		hy = max(hy, y+1)
	out = "\n"
	for y in range(ly, hy):
		for x in range(lx, hx):
			if (x + y*1j) in toColor:
				out += point
			else:
				out += space
		out+='\n'
	return out

def printCoords(coords, default = " "):
	# format of {pos:val}
	lx = hx = ly = hy = 0
	for p in coords.keys():
		x, y = imaginaryCoordToTuple(p)
		lx = min(lx, x)
		ly = min(ly, y)
		hx = max(hx, x)
		hy = max(hy, y)
	out = ""
	for y in range(ly, hy+1):
		for x in range(lx, hx+1):
			if (x + y*1j) in coords:
				out += coords[(x+y*1j)]
			else:
				out += default
		out+='\n'
	return out[:-1]