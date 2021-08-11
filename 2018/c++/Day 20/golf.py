grid = {(0, 0): 0}
dist = x = y = 0
stack = []

for char in open('Day 20/input').read()[1:-1]:
    if char == '(':
        stack.append((dist, x, y))
    elif char == ')':
        dist, x, y = stack.pop()
    elif char == '|':
        dist, x, y = stack[-1]
    else:
        x += (char == 'E') - (char == 'W')
        y += (char == 'S') - (char == 'N')
        dist += 1
        if (x, y) not in grid or dist < grid[(x, y)]:
            grid[(x, y)] = dist
print(grid)           
print('ans (part 1): %d' % max(grid.values()))
print('ans (part 2): %d' % sum(value >= 1000 for value in grid.values()))