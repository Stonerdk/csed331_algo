H, W = map(int, input().split())
arr = [[0] * W]
for i in range(H):
    arr.append([0] + list(map(int, input().split())))
dp = [[0 for _ in range(W + 1)] for _ in range(H + 1)]

dp[0][0] = arr[0][0]
for j in range(1, W):
    dp[0][j] = dp[0][j - 1] + arr[0][j]

for i in range(1, H):
    rdp, ldp = [0] * W, [0] * W
    ldp[W - 1] = dp[i - 1][W - 1] + arr[i][W - 1]
    for j in range(1, W + 1):
        rdp[j] = max(dp[i - 1][j], rdp[j - 1]) + arr[i][j]
        ldp[W + 1 - j] = max(dp[i - 1][W - 1 - j], ldp[W - j]) + arr[i][W - 1 - j]
    for j in range(W):
        dp[i][j] = max(ldp[j], rdp[j])

print(dp[H - 1][W - 1])    
