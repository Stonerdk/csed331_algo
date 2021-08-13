T = int(input())
sol = []
for t in range(T):
    N, M = map(int, input().split())
    grid = [list(map(int, input().split())) for _ in range(N)]
    dp = [[0] * M for _ in range(N)]

    # row 0
    dp[0][0] = grid[0][0]
    for j in range(1, M):
        dp[0][j] = dp[0][j - 1] + grid[0][j]
    
    for i in range(1, N):
        rdp = [0] * M
        ldp = [0] * M

        rdp[0] = dp[i - 1][0] + grid[i][0]
        for j in range(1, M):
            rdp[j] = max(dp[i - 1][j], rdp[j - 1]) + grid[i][j]
        
        ldp[M - 1] = dp[i - 1][M - 1] + grid[i][M - 1]
        for j in range(M - 2, -1, -1):
            ldp[j] = max(dp[i - 1][j], ldp[j + 1]) + grid[i][j]
        for j in range(M):
            dp[i][j] = max(ldp[j], rdp[j])
    sol.append(dp[N - 1][M - 1])
for s in sol:
    print(s)