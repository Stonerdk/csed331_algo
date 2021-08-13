T = int(input())
M = [2, 7, 22]
N = []
for t in range(T):
    N.append(int(input()))
maxN = max(N)
for i in range(maxN - 3):
    M.append((M[-1] * 3 + M[-2] - M[-3]) % 1000000000)
for n in N:
    print(M[n - 1])
