N, K = map(int, input().split())
coins = [int(input()) for _ in range(N)]
table = [1e10] * (K + 1)
table[0] = 0
for n in range(N):
    for k in range(1, K + 1):
        sub = k - coins[n]
        if sub >= 0 and table[sub] != -1:
            table[k] = min(table[k], table[sub] + 1)
print(table[K] if table[K] != 1e10 else -1)