# from collections import deque
# T, ans = int(input()), []
# for t in range(T):
#     N, K = map(int, input().split())
#     bits = []
#     for k in range(K):
#         bulbs = list(map(int, input().split()))
#         bbits = [1 << abs(x) >> 1 for x in bulbs]
#         cond, mask, conf = 0, 0, 0
#         for i, b in enumerate(bbits):
#             mask |= b 
#             conf |= b if bulbs[i] + bulbs[(i + 1) % 3] == 0 else 0
#             cond |= b if bulbs[i] > 0 else 0
#         bits.append((mask, cond, conf))
#     def subroutine():
#         for i in range(1 << N):
#             g = True
#             for mask, cond, conf in bits:
#                 g = g and (((i ^ ~cond) | conf & mask) != 0)
#             if g:
#                 return True
#         return False
#     ans.append(subroutine())
# for a in ans:
#     print("YES" if a else "NO")
# not passed