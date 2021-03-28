n, p = map(int, input().split())
lo, hi = p+1, p
last = 0
xs = []
x = 0
for _ in range(n):
    x = int(input())
    if not x:
        break
    xs.append(x)
    lo -= 1
    if x < last:
        hi -= 1
    last = x
#print(n, p, lo, hi, len(xs))
if hi != 1 and lo != 1:
    print("ambiguous")
else:
    all_lo = lo == 1
    last = 0
    for x in xs:
        if x < last:
            p -= 1
        if x == last and all_lo:
            p -= 1
        last = x
        print(p)
    for _ in range(len(xs), n):
        print(0)
