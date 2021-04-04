from queue import PriorityQueue
import math


def collision_time(drone1, drone2):
    if drone1[1] == drone2[1]:
        return None
    t = (drone2[0] - drone1[0]) / (drone1[1] - drone2[1])
    if t < 0:
        return None
    return t


n = int(input())
drones = [list(map(int, input().split())) for _ in range(n)]
alive = set(range(n))
succ = dict()
pred = dict()
for i in range(1, n):
    succ[i - 1] = i
    pred[i] = i - 1

# initial collisions on heap
pq = PriorityQueue()
for i in range(1, n):
    d1 = drones[i - 1]
    d2 = drones[i]
    t = collision_time(d1, d2)
    if t:
        pq.put((t, i - 1, i))
# while collisions left
while not pq.empty():
    # pop
    t, i, j = pq.get()
    # check
    if i not in alive or j not in alive:
        continue
    # kill i and j
    alive.remove(i)
    alive.remove(j)
    # insert new collision
    a = pred.get(i, None)
    b = succ.get(j, None)
    if a: succ[a] = b
    if b: pred[b] = a
    if a and b:
        t = collision_time(drones[a], drones[b])
        if t:
            pq.put((t, a, b))
print(len(alive))
print(' '.join(map(lambda x: str(x + 1), sorted(alive))))
