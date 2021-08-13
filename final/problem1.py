T = int(input())
sol = []
for t in range(T):
    N, M = map(int, input().split())
    arr = [list(map(int, input().split())) for _ in range(N)]
    dp = [[0 for _ in range(M)] for _ in range(N)]

    dp[0][0] = arr[0][0]
    for j in range(1, M):
        dp[0][j] = dp[0][j - 1] + arr[0][j]
    
    for i in range(1, N):
        dp[i][0] = dp[i - 1][0] + arr[i][0]
        for j in range(1, M):
            tb = [dp[i][j - 1], dp[i - 1][j], dp[i - 1][j - 1]]
            if i >= 2 and j >= 2:
                tb.append(dp[i - 2][j - 2])
            dp[i][j] = max(tb) + arr[i][j]
    
    sol.append(dp[N - 1][M - 1])
for s in sol:
    print(s)