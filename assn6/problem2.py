from collections import deque
T = int(input())
sol = []
for _ in range(T):
    v, e = map(int, input().split())
    nf = list(map(int, input().split()))
    nodes = [{} for _ in range(v + v)]
    for _ in range(e):
        s, d, c = map(int, input().split())
        nodes[s * 2 + 1][d * 2] = [0, c]
    for i in range(v):
        nodes[i * 2][i * 2 + 1] = [0, nf[i]]

    level = []
    def capacity(src, sink):
        if sink not in nodes[src]:
            return 0
        return nodes[src][sink][1] - nodes[src][sink][0]
    def dfs(src, acc):
        if src == v * 2 - 1:
            return acc
        for u in nodes[src]:
            if capacity(src, u) > 0 and level[u] == level[src] + 1 and level[u] <= level[v * 2 - 1]:
                g = dfs(u, acc + [(src, u)])
                if g:
                    return g
        return None
    def levelgraph():
        global level
        level = [-1 for _ in range(v + v)]
        level[0] = 0
        q = deque([0])
        while q:
            a = q.popleft()
            for d in nodes[a]:
                if level[d] == -1 and capacity(a, d) > 0:
                    level[d] = level[a] + 1
                    q.append(d)
    wacc = 0
    while True:
        levelgraph()
        if level[v * 2 - 1] == -1:
            break
        path = dfs(0, [])
        madd = min(capacity(s, d) for s, d in path)
        for s, d in path:
            nodes[s][d][0] += madd
        wacc += madd
    sol.append(wacc)
for s in sol:
    print(s)