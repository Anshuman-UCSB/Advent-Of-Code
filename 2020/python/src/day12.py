from utils.aocUtils import *

def p1s(instrs):
	pos = 0
	dir = 1
	for opc, arg in instrs:
		# print(opc, arg)
		if opc == "N":
			pos+=arg*1j
		elif opc == 'S':
			pos+=arg*-1j
		elif opc == 'E':
			pos+=arg
		elif opc == 'W':
			pos-=arg
		elif opc == 'R':
			dir *= pow(-1j,arg//90)
		elif opc == 'L':
			dir *= pow( 1j,arg//90)
		elif opc == 'F':
			pos += dir*arg
		# print(pos, dir)
	return imaginaryCoordToDist(pos)
def p2s(instrs):
	pos = 0
	way = 10+1j
	for opc, arg in instrs:
		# print(opc, arg)
		if opc == "N":
			way+=arg*1j
		elif opc == 'S':
			way+=arg*-1j
		elif opc == 'E':
			way+=arg
		elif opc == 'W':
			way-=arg
		elif opc == 'R':
			way *= pow(-1j,arg//90)
		elif opc == 'L':
			way *= pow( 1j,arg//90)
		elif opc == 'F':
			pos += way*arg
		# print(pos, way)
	return imaginaryCoordToDist(pos)
		
	
def main(input:str):
	instrs = [(x[0], int(x[1:])) for x in input.splitlines()]
	p1 = p1s(instrs)
	p2 = p2s(instrs)
	return (p1, p2)