# Has TLE!
from collections import Counter

N = int(input())
raw_rs = list(map(int, input().split()))
gs = dict()
for i, r in enumerate(raw_rs):
    current_gs = gs.get(r, [])
    current_gs.append(i + 1)
    gs[r] = current_gs
rs = Counter(raw_rs)
m = int(input())
ds = dict()
ns = dict()
for _ in range(m):
    a, b, d = map(int, input().split())
    a -= 1
    b -= 1
    ds[(a, b)] = d
    ds[(b, a)] = d
    current_ns = ns.get(a, set())
    current_ns.add(b)
    ns[a] = current_ns
    current_ns = ns.get(b, set())
    current_ns.add(a)
    ns[b] = current_ns

for r in rs:
    assignment = [0 for _ in range(N)]
    stack = []
    stack.append((0, r))
    while len(stack):
        a, r = stack.pop()
        if assignment[a] != 0:
            continue
        assignment[a] = r
        for n in ns[a]:
            if assignment[n] == 0:
                stack.append((n, ds[(a, n)] - r))
    valid = True
    check_rs = rs.copy()
    for a in range(N):
        if assignment[a] not in check_rs or check_rs[assignment[a]] == 0:
            valid = False
            break
        else:
            check_rs[assignment[a]] -= 1
    if valid:
        output = []
        for r in assignment:
            js = gs[r]
            output.append(str(js.pop()))
            gs[r] = js
        print(' '.join(output))
        exit()

print("impossible")
