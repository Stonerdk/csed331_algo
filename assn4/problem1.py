import heapq
def solution():
    N, C, D = map(int, input().split())
    maxHeap, minHeap, acc, cnt = [], [], C, 0
    for i in range(N):
        d, p = map(int, input().split())
        if d <= C:
            heapq.heappush(maxHeap, -p)
        elif d < D:
            heapq.heappush(minHeap, (d, p))
    heapq.heappush(minHeap, (D, 0))
    while minHeap:
        d, p = heapq.heappop(minHeap)
        while acc < d:
            if not maxHeap:
                return -1
            acc -= heapq.heappop(maxHeap)
            cnt += 1
        heapq.heappush(maxHeap, -p)
    return cnt   
T, sol = int(input()), []
for t in range(T):
    sol.append(solution())
for s in sol:
    print(s)