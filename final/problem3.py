T = int(input())
sol = []
for t in range(T):
    N, target = map(int, input().split())
    arr = list(map(int, input().split()))
    flag = False
    def dfs(acc, j):
        global N, arr, target, flag
        if j == N:
            if acc == target:
                flag = True
            return
        dfs(acc + arr[j], j + 1)
        dfs(acc, j + 1)
    dfs(0, 0)
    sol.append("YES" if flag else "NO")
for s in sol:
    print(s)