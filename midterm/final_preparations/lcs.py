S1 = input()
S2 = input()
dp = [[0 for _ in range(len(S2) + 1)] for _ in range(len(S1) + 1)]
for i in range(len(S1)):
    for j in range(len(S2)):
            dp[i + 1][j + 1] = dp[i][j] + 1 if S1[i] == S2[j] else max(dp[i][j + 1], dp[i + 1][j])
print(dp[-1][-1])