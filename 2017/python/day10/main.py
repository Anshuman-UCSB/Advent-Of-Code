def day10(input):
	*nums,=range(256)
	pos = 0
	ss=0
	def wrap(n):
		return n%256
	try:
		for l in map(int,input.split(',')):
			# print(nums[pos:pos+l-1])
			for i in range(l//2):
				nums[wrap(pos+i)],nums[wrap(pos+l-i-1)]=nums[wrap(pos+l-i-1)],nums[wrap(pos+i)]
			pos=wrap(pos+l+ss)
			ss+=1
			# print(nums)
			# print(nums[pos])
	except ValueError:
		print("Skipping p1")
	p1=nums[0]*nums[1]
	
	swaps = [ord(c) for c in input]+[17, 31, 73, 47, 23]
	*nums,=range(256)
	pos = 0
	ss=0
	
	for l in swaps*64:
		# print(nums[pos:pos+l-1])
		for i in range(l//2):
			nums[wrap(pos+i)],nums[wrap(pos+l-i-1)]=nums[wrap(pos+l-i-1)],nums[wrap(pos+i)]
		pos=wrap(pos+l+ss)
		ss+=1
	p2=""
	for i in range(0,256,16):
		v = 0
		for j in range(16):
			v^=nums[i+j]
		p2+=(hex(v)[2:]).zfill(2)
	return [p1,p2]