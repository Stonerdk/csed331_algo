T, sol = int(input()), []
for i in range(T):
    L, N = map(int, input().split())
    pos = list(map(int, input().split()))
    prices = list(map(int, input().split()))
    mprice, prevdist, acc = prices[0], 0, 0
    for i in range(1, N):
        acc += (pos[i] - prevdist) * mprice
        mprice = min(mprice, prices[i])
        prevdist = pos[i]
    acc += (L - prevdist) * mprice
    sol.append(acc)
for s in sol:
    print(s)

    