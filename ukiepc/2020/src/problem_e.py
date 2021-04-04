rows, cols = map(int, input().split())

bs = []
plan = []
heights = []
blocks = 0
for y in range(rows):
    row = []
    for x, h in enumerate(map(int, input().split())):
        heights.append((x, y, h))
        row.append(h)
        if h:
            blocks += 1
    plan.append(row)


def build_elevator(plan, n, x, y):
    ns = [(plan[y][x], x, y)]
    while len(ns):
        h, x, y = ns.pop()
        if x < 0 or x >= len(plan[0]):
            continue
        if y < 0 or y >= len(plan):
            continue
        if plan[y][x] > h:
            continue
        if plan[y][x] == 0:
            continue
        h = plan[y][x]
        plan[y][x] = 0
        n -= 1
        ns.extend([(h, x - 1, y), (h, x + 1, y), (h, x, y - 1), (h, x, y + 1)])
    return n


total = 0
heights = list(filter(lambda x: x[2] > 1, heights))
heights.sort(key=lambda x: x[2], reverse=True)
for x, y, h in heights:
    if plan[y][x] == 0:
        continue
    blocks = build_elevator(plan, blocks, x, y)
    total += 1
print(total)