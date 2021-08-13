mp = {}
def star(N):
    if (N == 3):
        return ["  *", " * *", "*****"]
    if N in mp:
        return mp[N]
    g = []
    hsize = N // 2
    prev = star(hsize)
    for i in range(hsize):
        g.append(" " * hsize + prev[i])
    for i in range(hsize):
        g.append(prev[i] + " " * (hsize - i) + prev[i])
    mp[N] = g
    return g
T = int(input())
sizes = []
for t in range(T):
    size = int(input())
    sizes.append(size)
for size in sizes:
    stars = star(size)
    for s in stars:
        print(s)