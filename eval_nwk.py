import networkit as nk

import sys
import time

instance = sys.argv[1]

### Reader

timer_nk_start = time.time()
G = nk.readGraph(instance)
timer_nk_end = time.time()
print(timer_nk_end - timer_nk_start)

G = nk.graphtools.toUndirected(G)
G.removeMultiEdges()
G.removeSelfLoops()

print(G.numberOfEdges())


### PLM

timer_nk_start = time.time()
alg = nk.community.PLM(G)
alg.run()
timer_nk_end = time.time() 
print(timer_nk_end - timer_nk_start)

timer_nk_start = time.time()
alg.getPartition()
timer_nk_end = time.time()
print(timer_nk_end - timer_nk_start)
