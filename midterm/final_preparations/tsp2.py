N = int(input())
graph = [[] for _ in range(N)]
for i in range(N):
    row = list(map(int, input().split()))
    for t in enumerate(row):
        graph[i].append(t)

minvalue = 1e10
def dfs(v, vis, acc):
    global minvalue
    if v == 0 and vis == (1 << N) - 1:
        minvalue = min(minvalue, acc)
    for u, cost in graph[v]:
        if vis >> u & 1 == 0:
            dfs(u, vis | (1 << u), acc + cost)
dfs(0, 0, 0)
print(minvalue)