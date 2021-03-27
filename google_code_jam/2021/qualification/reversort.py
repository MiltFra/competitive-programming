def cost_of_case():
    n = int(input())
    ls = list(map(int, input().split()))
    c = 0
    for i in range(n - 1):
        j = i
        for k in range(j + 1, n):
            if ls[k] < ls[j]:
                j = k
        ls[i:j+1] = reversed(ls[i:j+1])
        c += j - i + 1
    return c


t = int(input())
for i in range(t):
    c = cost_of_case()
    print(f"Case #{i+1}: {c}")
