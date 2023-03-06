def day17(input):
	ss=int(input)
	arr=[0]
	i=0
	for v in range(1,2018):
		i=1+((i+ss)%len(arr))
		arr.insert(i,v)
		# print(arr,i)
	p1 = arr[(i+1)%len(arr)]

	l=1
	i=0
	for v in range(1,50000000):
		i=1+((i+ss)%l)
		l+=1
		if i==1:
			p2=v
	return [p1,p2]