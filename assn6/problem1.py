T, sol = int(input()), []
for t in range(T):
    n, m, l = map(int, input().split())
    gl, rm, s = [[] for _ in range(n)], [-1] * m, 0
    for i in range(l):
        a, b = map(int, input().split())
        gl[a].append(b)
    def dfs(i, visited):
        visited[i] = True
        for j in gl[i]:
            if rm[j] == -1 or (not visited[rm[j]] and dfs(rm[j], visited)):
                rm[j] = i
                return True
        return False
    for i in range(n):
        if dfs(i, [False] * n):
            s += 1
    sol.append(s)
for s in sol:
    print(s)