def is_wall(x, y):
    value = x * x + 3 * x + 2 * x * y + y + y * y + 1352
    one_bits = bin(value).count('1')
    return one_bits % 2 == 1


traversed = {(1, 1)}
steps = 0
new_places = traversed

part1 = None
part2 = None

while part1 is None or part2 is None:
    places_to_check = new_places.copy()
    new_places = set()
    for old_x, old_y in places_to_check:
        for x, y in [(old_x + 1, old_y), (old_x - 1, old_y), (old_x, old_y + 1), (old_x, old_y - 1)]:
            if x < 0 or y < 0 or (x, y) in traversed or is_wall(x, y):
                continue
            traversed.add((x, y))
            new_places.add((x, y))
    steps += 1
    if (31, 39) in new_places:
        part1 = steps
    if steps == 50:
        part2 = len(traversed)

print(part1)
print(part2)