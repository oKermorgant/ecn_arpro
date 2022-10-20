from time import time

try:
    travel = reload(travel)
except:
    import travel

import ga
import sys

if len(sys.argv) == 1:
    from xy import XY as Indiv
else:
    Indiv = travel.Travel
    Indiv.load('tsp.yaml')
print('Best:')

start = time()

ga.ga(Indiv).display()

end = time()

print(f'Took {1000*(end-start)} ms')

# compare to best out of 100
best = Indiv()
best.randomize()
best.compute_cost()
for i in range(10000):
    indiv = Indiv()
    indiv.randomize()
    indiv.compute_cost()
    if indiv.cost < best.cost:
        best = indiv
print('Random:')
best.display()
