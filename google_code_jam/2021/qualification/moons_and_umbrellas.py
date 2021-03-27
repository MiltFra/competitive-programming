def cost(x, y, a, b):
    if a == 'C' and b == 'J':
        return x
    if a == 'J' and b == 'C':
        return y
    return 0


t = int(input())
for i in range(t):
    x, y, s = input().split()
    x = int(x)
    y = int(y)
    p = 0
    c = s[0]
    for j in range(1, len(s)):
        if s[j] == '?':
            continue
        if s[j] != 'c':
            p += cost(x, y, c, s[j])
        c = s[j]
    print(f"Case #{i+1}: {p}")
