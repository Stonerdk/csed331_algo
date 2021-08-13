N, T = map(int, input().split())
glist = list(map(int, input().split()))
maxsum = 0
for i in range(N - 2):
    for j in range(i + 1, N - 1):
        for k in range(j + 1, N):
            s = glist[i] + glist[j] + glist[k]
            if s <= T:
                maxsum = max(maxsum, s)
print(maxsum)