from collections import defaultdict, deque
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
    def __init__(self, N):
        self.body = [defaultdict(Edge) for i in range(N)]
        self.size = N
    def connect(self, src, dest, capacity):
        self.body[src - 1][dest - 1].add_capacity(src - 1, dest - 1, capacity, True)
        self.body[dest - 1][src - 1].add_capacity(dest - 1, src - 1, 0, False)
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
            p = self.fill_path(0, self.size - 1)
            #print(p)
            if not p:
                break
        #self.tostring()
    def get_saturated_edges(self):
        sig = 0
        for arr in self.body:
            for edge in arr.values():
                if edge.valid and not edge.flowable():
                    p = self.find_path(edge.src, edge.dest)
                    if not p:
                        sig += edge.bandwidth
        return sig
    def tostring(self):
        for arr in self.body:
            for edge in arr.values():
                print(edge.src, "->", edge.dest, edge.flow, " / ", edge.capacity)
        
T = int(input())
sol = []
for _ in range(T):
    N, M = map(int, input().split())
    net = Network(N)
    for _ in range(M):
        src, dest, cap = map(int, input().split())
        net.connect(src, dest, cap)
    net.maxflow()
    sig = net.get_saturated_edges()
    sol.append(sig)
for s in sol:
    print(s)
    
        
    
        
