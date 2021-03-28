from sys import exit


def read_map(l):
    m = []
    for _ in range(l):
        s = input().strip()
        if s == '?':
            m.append(None)
        else:
            s = s.split()
            m.append((s[0], int(s[1])))
    return m


m, n = map(int, input().split())
map1 = read_map(m)
map2 = read_map(n)
total = 0
for i in range(m - n + 1):
    matching = True
    for j in range(n):
        x = map1[i + j]
        y = map2[j]
        if x and y and x != y:
            matching = False
            break
    if matching:
        total += 1
print(total)