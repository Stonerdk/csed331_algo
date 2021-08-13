from collections import defaultdict, deque

T = int(input())

class Edge:
    def __init__(self):
        self.capacity = 0
        self.flow = 0
    def capable(self):
        return self.flow < self.capacity
    def residue(self):
        return self.capacity - self.flow

sol = []
for t in range(T):
    V, E = map(int, input().split())
    NW = [defaultdict(Edge) for _ in range(2 * V)]
    NC = list(map(int, input().split()))
    for i, c in enumerate(NC):
        NW[i * 2][i * 2 + 1].capacity = c
    for _ in range(E):
        s, d, c = map(int, input().split())
        NW[s * 2 + 1][d * 2].capacity = c
    SINK = 2 * V - 1
    
    levels = []
    def dfs(now, flow):
        if now == SINK:
            return flow
        for next, edge in NW[now].items():
            if levels[next] == levels[now] + 1 and edge.capable():
                f = dfs(next, min(edge.residue(), flow))
                if f > 0:
                    NW[now][next].flow += f
                    NW[next][now].flow -= f
                    return f
        return 0
    
    gain = 0
    while True:
        levels = [-1] * (2 * V)
        levels[0] = 0

        q = deque([0])
        while q:
            now = q.popleft()
            if now == SINK:
                break
            for next, edge in NW[now].items():
                if levels[next] == -1 and edge.capable():
                    levels[next] = levels[now] + 1
                    q.append(next)
        if levels[SINK] == -1:
            sol.append(gain)
            break
        gain += dfs(0, 1e10)

for s in sol:
    print(s)



