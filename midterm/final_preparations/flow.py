from collections import defaultdict, deque
import sys
class Edge:
    def __init__(self):
        self.src = 0
        self.dest = 0
        self.flow = 0
        self.capacity = 0
        self.bandwidth = 0
        self.valid = False
    def add_capacity(self, src, dest, capacity, trueflow):
        if self.valid == False:
            self.src = src
            self.dest = dest
            self.valid = True
        self.capacity += capacity
        self.valid = True
        if trueflow:
            self.bandwidth += 1
    def flowable(self):
        return self.flow < self.capacity and self.bandwidth != 0 and self.valid

class Network:
    def __init__(self, N, source, sink):
        self.body = [defaultdict(Edge) for i in range(N)]
        self.size = N
        self.source = source
        self.sink = sink
    def connect(self, src, dest, capacity):
        self.body[src - 1][dest - 1].add_capacity(src - 1, dest - 1, capacity, True)
        self.body[dest - 1][src - 1].add_capacity(dest - 1, src - 1, capacity, True)
    def find_path(self, src, dest):
        que = deque([(src, 0, [])])
        while que:
            node, visited, getpath = que.popleft()
            visited |= 1 << node
            if node == dest:
                return getpath
            for edge in self.body[node].values():
                if edge.flowable() and visited >> edge.dest & 1 == 0:
                    que.append((edge.dest, visited, getpath + [edge]))
        return False
    def fill_path(self, src, dest):
        path = self.find_path(src, dest)
        if not path:
            return False
        #for p in path:
            #print(p.src, p.dest, p.flow, "/", p.capacity)
        minedge = min(path, key = lambda e : e.capacity - e.flow)
        amount = minedge.capacity - minedge.flow
        for edge in path:
            edge.flow += amount
            self.body[edge.dest][edge.src].flow -= amount
        
        return True
    def maxflow(self):
        while(True):
            p = self.fill_path(self.source, self.sink)
            #print(p)
            if not p:
                break
        mf = 0
        #self.tostring()
        for edge in self.body[self.source].values():
            mf += edge.flow
        return mf

    def tostring(self):
        for arr in self.body:
            for edge in arr.values():
                print(edge.src, "->", edge.dest, edge.flow, " / ", edge.capacity)

def toIdx(chr):
    if chr[0].isupper():
        return ord(chr) - ord('A') + 1
    else:
        return ord(chr) - ord('a') + 26 + 1


sol = []

M = int(input())
net = Network(52, 0, 25)
for _ in range(M):
    [src, dest, cap] = input().split()
    src = toIdx(src)
    dest = toIdx(dest)
    cap = int(cap)
    net.connect(src, dest, cap)
mf = net.maxflow()
print(mf)

    
        
    
        
