import math


def find_best(a):
    best_r, best_i = a[1], 1
    for i in range(2, len(a)):
        if a[i] / i < best_r:
            best_i = i
            best_r = a[i] / i
    return best_i


def extend_dynamic(data, best, n):
    i = n
    last_not_used = n
    while i - last_not_used < n + 3:
        data.append(math.inf)
        i += 1
        data[i] = data[best] + data[i - best]
        for j in range(1, n + 1):
            s = data[j] + data[i - j]
            if s < data[i]:
                data[i] = s
                last_not_used = i
        print(data)


n, q = map(int, input().split())
data = list(map(int, input().split()))
data = [0] + data

best = find_best(data)
extend_dynamic(data, best, n)
print(data)

for _ in range(q):
    k = int(input())
    if k < len(data):
        print(data[k])
        continue
    fitting = 1 + (k - (len(data) - 1)) // best
    rest = k - fitting * best
    print(data[best] * fitting + data[rest])

# read inputs