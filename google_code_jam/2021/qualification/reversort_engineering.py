def generate_sequence(n, c):
    if c < n - 1:
        return None
    if c >= n * (n + 1) / 2:
        return None
    if n == 1:
        return []
    for i in range(n, 0, -1):
        s = generate_sequence(n - 1, c - i)
        if s != None:
            s.append(i)
            return s
    return None


def construct_list():
    n, c = map(int, input().split())
    xs = generate_sequence(n, c)
    if not xs:
        return None
    ls = list(range(1, n + 1))
    for i, x in enumerate(xs):
        idx = n - i - 2
        ls[idx:idx + x] = reversed(ls[idx:idx + x])
    return ls


t = int(input())
for i in range(t):
    ls = construct_list()
    if ls:
        print(f"Case #{i+1}: {' '.join(map(str, ls))}")
    else:
        print(f"Case #{i+1}: IMPOSSIBLE")