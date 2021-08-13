from collections import deque

V = int(input())
SRC = V
SINK = V + 1
INF = 1e10
ADJ = [[0 for _ in range(V + 2)] for _ in range(V + 2)]
FLOW = [[0 for _ in range(V + 2)] for _ in range(V + 2)]
pref = list(map(int, input().split()))
for i in range(V):
    ADJ[i] = list(map(int, input().split())) + [0, 0]
for (i, p) in enumerate(pref):
    if p == 1 or p == 0:
        ADJ[SRC][i] = 1e10
    elif p == 2 or p == 0:
        ADJ[i][SINK] = 1e10

def levelgraph():
    levels = [INF for _ in range(V + 2)]
    levels[SRC] = 0
    q = deque([SRC])
    while q:
        now = q.popleft()
        for next in range(V + 2):
            if ADJ[now][next] - FLOW[now][next] > 0 and levels[next] == INF:
                levels[next] = levels[now] + 1 
                q.append(next)
    return levels, levels[SINK] != INF

def dfs(v, level, flow):
    if v == SINK:
        return flow
    for next in range(V + 2):
        if level[next] == level[v] + 1 and ADJ[v][next] > FLOW[v][next]:
            f = dfs(next, level, min(flow, ADJ[v][next] - FLOW[v][next]))
            if f > 0:
                FLOW[v][next] += f
                FLOW[next][v] -= f
                return f
    return 0

while True:
    level, valid = levelgraph()
    if not valid:
        ss = [str(i + 1) for i, l in enumerate(level[:V]) if l != INF]
        ls = [str(i + 1) for i, l in enumerate(level[:V]) if l == INF]
        print(sum(FLOW[SRC]))
        print(" ".join(ss))
        print(" ".join(ls))
        break
    dfs(SRC, level, INF)


