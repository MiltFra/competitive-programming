input()
xs = [int(x) for x in input().split()]
ys = [int(y) for y in input().split()]
zs = [int(z) for z in input().split()]


def median(x, y, z):
    if x <= y <= z or x >= y >= z:
        return y
    if y <= x <= z or y >= x >= z:
        return x
    return z

print(' '.join([str(median(x, y, z)) for (x, (y, z)) in zip(xs, zip(ys, zs))]))
