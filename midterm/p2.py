from collections import deque
T = int(input())
sol = []
for _ in range(T):
    V, E = map(int, input().split())
    dests = [{} for _ in range(V)]
    dp = [6000000 for _ in range(V)]
    visited = [False for _ in range(V)]
    for _ in range(E):
        s, d, w = map(int, input().split())
        if d in dests[s]:
            if w < dests[s][d][0]:
                dests[s][d] = [w, False]
        else:
            dests[s][d] = [w, False]
    dp[0] = 0
    for i in range(V):
        Q = deque([0])
        while Q:
            cur = Q.popleft()
            for d in dests[cur]:
                if dp[d] > dp[cur] + dests[cur][d][0] and not dests[cur][d][1]:
                    dp[d] = dp[cur] + dests[cur][d][0]
                    Q.append(d)
    sol.append(dp[V-1])
for s in sol:
    if s == 6000000:
        print("NO")
    else:
        print(s)
