def inputMatrix():
    return []

A = inputMatrix()
N = len(A)
red, blue, rpos, bpos, tail = [0], [], 0, 0, 0
for i in range(1, N):
    if A[0][i]:
        red.append(i)
    else:
        blue.append(i)
if len(red) == 1 or len(red) == N:
    return False
elif len(red) == N - 1:
    tail = blue[0]