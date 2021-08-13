Base = [[3, 1, -1], [1, 0, 0], [0, 1, 0]]
Initial = [22, 7, 2]
Divnum = 1234567890

def mmul(A, B):
    C = [[0, 0, 0], [0, 0, 0], [0, 0, 0]]
    for i in range(3):
        for j in range(3):
            for k in range(3):
                C[i][j] += A[i][k] * B[k][j]
                if C[i][j] >= Divnum:
                    C[i][j] %= Divnum
    return C
def msq(N):
    if N == 1:
        return Base
    D = msq(N // 2)
    C = mmul(D, D)
    if N % 2 == 1:
        return mmul(C, Base)
    return C

def last(a, b, c):
    acc = 0
    acc = (acc + a * 22) % Divnum
    acc = (acc + b * 7) % Divnum
    acc = (acc + c * 2) % Divnum
    return acc
T = int(input())
sol = []
for t in range(T):
    n = int(input())
    if n <= 3:
        sol.append(Initial[3 - n])
    else:
        Q = msq(n - 3)
        sol.append(last(Q[0][0], Q[0][1], Q[0][2]))
for s in sol:
    print(s)