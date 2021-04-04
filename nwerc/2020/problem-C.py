n, k = map(int, input().split())
d, s = map(int, input().split())

ans = (n * d - k * s) / (n - k)
if ans > 100 or ans < 0:
    print("impossible")
else:
    print(ans)
