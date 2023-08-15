def main(input):
	p = 0
	d = 1
	for i in input.splitlines():
		match i[0]:
			case "N":p+=1j	* int(i[1:])
			case "S":p-=1j	* int(i[1:])
			case "E":p+=1	* int(i[1:])
			case "W":p-=1	* int(i[1:])
			case "F":p+=d	* int(i[1:])
			case "R":d /= 1j ** (int(i[1:])//90)
			case "L":d *= 1j ** (int(i[1:])//90)
	p1 = int(abs(p.real) + abs(p.imag))
	
	p = 0
	wp = 10+1j
	for i in input.splitlines():
		match i[0]:
			case "N":wp+=1j	* int(i[1:])
			case "S":wp-=1j	* int(i[1:])
			case "E":wp+=1	* int(i[1:])
			case "W":wp-=1	* int(i[1:])
			case "F":p+=wp	* int(i[1:])
			case "R":wp /= 1j ** (int(i[1:])//90)
			case "L":wp *= 1j ** (int(i[1:])//90)
	p2 = int(abs(p.real) + abs(p.imag))

	return p1, p2