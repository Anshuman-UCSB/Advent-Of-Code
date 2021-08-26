import numpy as np

def main(input:str) -> tuple:
	wires = {}
	while 'a' not in wires:
		for l in input.splitlines():
			spl = l.split()
			if len(spl) == 3:
				try:
					wires[spl[-1]] = np.uint16(spl[0])
				except:
					if spl[0] in wires:
						wires[spl[-1]] = wires[spl[0]]
			else:
				try:
					if spl[1] == "AND":
						if spl[0] == "1":
							wires[spl[-1]] = 1 & wires[spl[2]]
						else:
							wires[spl[-1]] = wires[spl[0]] & wires[spl[2]]
					elif spl[1] == "LSHIFT":
						wires[spl[-1]] = wires[spl[0]] << int(spl[2])
					elif spl[1] == "OR":
						wires[spl[-1]] = wires[spl[0]] | wires[spl[2]]
					elif spl[1] == "RSHIFT":
						wires[spl[-1]] = wires[spl[0]] >> int(spl[2])
					elif spl[0] == "NOT":
						wires[spl[-1]] = ~wires[spl[1]]
				except Exception as e:
					pass
	p1 = wires['a']
	wires = {}
	while 'a' not in wires:
		for l in input.splitlines():
			spl = l.split()
			if len(spl) == 3:
				try:
					wires[spl[-1]] = np.uint16(spl[0])
					wires['b'] = p1
				except:
					if spl[0] in wires:
						wires[spl[-1]] = wires[spl[0]]
			else:
				try:
					if spl[1] == "AND":
						if spl[0] == "1":
							wires[spl[-1]] = 1 & wires[spl[2]]
						else:
							wires[spl[-1]] = wires[spl[0]] & wires[spl[2]]
					elif spl[1] == "LSHIFT":
						wires[spl[-1]] = wires[spl[0]] << int(spl[2])
					elif spl[1] == "OR":
						wires[spl[-1]] = wires[spl[0]] | wires[spl[2]]
					elif spl[1] == "RSHIFT":
						wires[spl[-1]] = wires[spl[0]] >> int(spl[2])
					elif spl[0] == "NOT":
						wires[spl[-1]] = ~wires[spl[1]]
				except Exception as e:
					pass
	return (p1, wires['a'])