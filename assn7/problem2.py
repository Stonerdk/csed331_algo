T, sol = int(input()), []
for t in range(T):
    V, E = map(int, input().split())
    G = [{} for _ in range(V)]
    for e in range(E):
        s, d, c = map(int, input().split())
        G[s][d], G[d][s] = c, c
    mask, mdist = (1 << V) - 1, 2e10
    def subroutine(node, v, acc):
        global mdist
        nv = v | (1 << node)
        if ~nv & mask == 0:
            if 0 in G[node]:
                mdist = min(mdist, acc + G[node][0])
                return
        for d in G[node]:
            if nv >> d & 1 == 0:
                subroutine(d, nv, acc + G[node][d])
    subroutine(0, 0, 0)
    sol.append(mdist if mdist != 2e10 else -1)
for s in sol:
    print(s)