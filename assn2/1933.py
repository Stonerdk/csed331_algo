from collections import deque 
N = int(input())
buildings = []

def merge(left, right):
    res, ly, ry, latest = deque(), 0, 0, 0
    while True:
        if not left:
            return res + right
        elif not right:
            return res + left
        else:
            X, Y = left[0][0], right[0][0]
            if X >= Y:
                xx, ry = right.popleft()
            if X <= Y:
                xx, ly = left.popleft()
            u = max(ly, ry)
            if latest != u:
                res.append((xx, u))
                latest = u

def getVector(s, e):
    if e == s + 1:
        return deque(buildings[s])
    pivot = (s + e) // 2
    return merge(getVector(s,pivot), getVector(pivot,e))

for _ in range(N):
    x1, y, x2 = map(int, input().split())
    buildings.append([(x1, y), (x2, 0)])

tmp, res, y = getVector(0, N), [], 0
print(tmp)
for t in tmp:
    res.append((t[0],y))
    res.append((t[0],t[1]))
    y = t[1]