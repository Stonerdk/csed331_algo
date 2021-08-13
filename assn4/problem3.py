T, values, sol = int(input()), [], []

def dnq(start, end):
    if end <= start: 
        return 0
    if end == start + 1: 
        return values[start][2] * (values[start][1] - values[start][0])
    minidx, minv = min(enumerate(values[start:end]), key = lambda x: x[1][2])
    return max((values[end - 1][1] - values[start][0]) * minv[2], dnq(start, start + minidx), dnq(start + minidx + 1, end))

for _ in range(T):
    N, W = map(int, input().split())
    values = []
    for i in range(N):
        values.append(tuple(map(int, input().split())))
    sol.append(dnq(0, N))

for s in sol:
    print(s)