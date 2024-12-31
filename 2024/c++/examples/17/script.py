def test(A):
    out = []
    B=C=0
    while A:
        B=A%8
        B^=2
        C = A>>B
        B ^= C
        A >>= 3
        B ^= 7
        # print(f"{B%8} ({B}%8)")
        out.append(B%8)
    return out

def test2(A):
    out = []
    B=C=0
    while A:
        B=(A%8)^2
        C = A>>B
        B ^= C^7
        A >>= 3
        out.append(B%8)
    return "".join(map(str,out))

ans = "101"
target = "".join(map(str,[2,4,1,2,7,5,4,5,0,3,1,7,5,5,3,0]))
# print(test2(int(ans,2)))
while(len(target) > (len(ans)/3)):

    for i in range(8):
        # assert test(i) == test2(i)
        i = ((int(ans,2))<<3) + i
        print(bin(i),test(i),sep='\t')
        if target.endswith(test2(i)):
            ans = bin(i)[2:]
            print(ans)
            break

nums = [4,5,7,1,0,3,2]
print("A:",int(ans,2))
# 5 3 0         0b101011010
# 5 5 3 0       0b101011010010
# 7 5 5 3 0     0b101011010010011
# 1 7 5 5 3 0   0b101011010010011101