with open("day22") as file:
    data = file.read().strip().split('\n\n')
    
def game(X, Y):          # player X & Y
    occur = []
    while X and Y:
        if X in occur:
            flag = True  # X wins
            break        # infinity
        else:
            occur.append(X[:])
        x, y = X.pop(0), Y.pop(0)
        if x <= len(X) and y <= len(Y):
            _, flag = game(X[:x], Y[:y])
            (X.append(x), X.append(y)) if flag else (Y.append(y), Y.append(x))
        else:
            (X.append(x), X.append(y), flag := True) if x > y else (Y.append(y), Y.append(x), flag := False)
    return X if X else Y, flag

X, Y = [[int(n) for n in d.split('\n')[1:]] for d in data]
while X and Y:
    x, y = X.pop(0), Y.pop(0)
    (X.append(x), X.append(y)) if x > y else (Y.append(y), Y.append(x))
print('Part One:', sum(e * (len(X if X else Y) - i) for i, e in enumerate(X if X else Y)))

winner = game(*[[int(n) for n in d.split('\n')[1:]] for d in data])[0]
print('Part Two:', sum(e * (len(winner) - i) for i, e in enumerate(winner)))