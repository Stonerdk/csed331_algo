def findIdx(data, l, start, end):
    center = (start + end) // 2
    if start == end:
        return end
    if data <= l[center]:
        return findIdx(data, l, start, center)
    else:
        return findIdx(data, l, center + 1, end)
T = int(input())
sol = []
for i in range(T):
    _ = int(input())
    A = list(map(int, input().split()))
    dpl = []
    for a in A:
        if not dpl or a > dpl[-1]:
            dpl.append(a)
        else:
            idx = findIdx(a, dpl, 0, len(dpl) - 1)
            dpl[idx] = a
    sol.append(len(dpl))
for s in sol:
    print(s)