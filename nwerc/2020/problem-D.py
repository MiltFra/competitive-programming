def find_ball():
    x0 = y0 = 0
    x1 = y1 = 10**6
    while True:
        dx = (x1 - x0)
        dy = y1 - y0
        print(x0 + (x1 - x0) // 4, y0 + (y1 - y0) // 4, flush=True)
        d0 = int(input())
        if d0 == 0:
            break
        print(x0 + dx // 4, y1 - dy // 4, flush=True)
        d1 = int(input())
        if d1 == 0:
            break
        print(x1 - dx // 4, y0 + dy // 4, flush=True)
        d2 = int(input())
        if d2 == 0:
            break
        print(x1 - dx // 4, y1 - dy // 4, flush=True)
        d3 = int(input())
        if d3 == 0:
            break
        best = min(d0, d1, d2, d3)
        xc = (x0 + x1) // 2
        yc = (y0 + y1) // 2
        if best == d0 or best == d1:
            x1 = xc
        else:
            x0 = xc
        if best == d0 or best == d2:
            y1 = yc
        else:
            y0 = yc


n = int(input())
for _ in range(n):
    find_ball()