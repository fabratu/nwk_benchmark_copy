import networkit as nk

import sys
import time

instance = sys.argv[1]
type = sys.argv[2]

### Reader


G = nk.readGraph(instance)
G.removeMultiEdges()
G.removeSelfLoops()

### PLM

if type == "PLM":
    for i in range(50):
        print("Run: ", i + 1)
        timer_nk_start = time.time()
        alg = nk.community.ParallelLeiden(G)
        timer_nk_end = time.time()
        print("PLM construction time: ", timer_nk_end - timer_nk_start)

        timer_nk_start = time.time()
        alg.run()
        timer_nk_end = time.time() 
        print("PLM runtime: ", timer_nk_end - timer_nk_start)

        timer_nk_start = time.time()
        part = alg.getPartition()
        timer_nk_end = time.time()
        print("Partition extraction runtime: ", timer_nk_end - timer_nk_start)

        timer_nk_start = time.time()
        mod = nk.community.Modularity()
        modularity = mod.getQuality(part, G)
        timer_nk_end = time.time()
        print("Modularity computation runtime: ", timer_nk_end - timer_nk_start)

elif type == "PLL":
    for i in range(50):
        print("Run: ", i + 1)
        timer_nk_start = time.time()
        alg = nk.community.ParallelLeiden(G)
        timer_nk_end = time.time()
        print("PLL construction time: ", timer_nk_end - timer_nk_start)

        timer_nk_start = time.time()
        alg.run()
        timer_nk_end = time.time() 
        print("PLL runtime: ", timer_nk_end - timer_nk_start)

        timer_nk_start = time.time()
        part = alg.getPartition()
        timer_nk_end = time.time()
        print("Partition extraction runtime: ", timer_nk_end - timer_nk_start)

        timer_nk_start = time.time()
        mod = nk.community.Modularity()
        modularity = mod.getQuality(part, G)
        timer_nk_end = time.time()
        print("Modularity computation runtime: ", timer_nk_end - timer_nk_start)