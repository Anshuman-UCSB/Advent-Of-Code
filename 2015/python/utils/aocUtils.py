import re
from functools import reduce
from _md5 import md5

def hash(inp):
	return md5(inp.encode()).hexdigest()

def printAnswer(result : tuple):
	print("[P1]",result[0])
	print("[P2]",result[1])

def imaginaryCoordToDist(n: complex):
	return int(abs(n.real)) + int(abs(n.imag))
	
def imaginaryCoordToTuple(n: complex):
	return (int(abs(n.real)) , int(abs(n.imag)))

def readNums(inp):
	return list(map(int, re.findall(r"(-?\d+)", inp)))

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