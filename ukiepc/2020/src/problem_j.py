from sys import exit
from math import ceil, sqrt
c, e, m = map(int, input().split())
if c != 4 or e % 2:
    print("impossible")
    exit(0)
max_w = e // 2
min_w = (max_w + 1) // 2
for w in range(min_w, max_w + 1):
    h = e // 2 - w
    if m == w * h:
        print(max(w, h) + 2, min(w, h) + 2)
        exit(0)
print("impossible")
