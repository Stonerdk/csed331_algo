import heapq

def find(u):
    if u == union[u]:
        return u
    union[u] = find(union[u])
    return union[u]
def merge(u, v):
    a, b = find(u), find(v)
    if a == b:
        return 0
    if (rank[a] < rank[b]):
        a, b = b, a
    union[b] = a
    ret = setnum[a] * setnum[b]
    setnum[a] += setnum[b]
    setnum[b] = 0
    if (rank[a] == rank[b]):
        rank[a] += 1
    return ret

T, sol = int(input()), []
for _ in range(T):
    N, M = map(int, input().split())
    edges, union, rank, setnum, cost, sm = [], list(range(N)), [1 for _ in range(N)], [1 for _ in range(N)], 0, 0
    for _ in range(M):
        s, d, e = map(int, input().split())
        sm += e
        heapq.heappush(edges, (-e, s, d))
    while edges:
        e, s, d = heapq.heappop(edges)
        cost = (cost + merge(s, d) * sm) % 1000000000
        sm += e
    sol.append(cost)
for s in sol:
    print(s)