from utils.aocUtils import *
from operator import mul
def main(input:str):
	n = readNums(input)
	return (prod([(a,b) for a in n for b in n if a+b==2020][0]),prod([(a,b,c) for a in n for b in n for c in n if a+b+c==2020][0]))