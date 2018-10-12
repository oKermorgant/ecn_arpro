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
ga.ga(Indiv).display()

# compare to best out of 100
best = Indiv()
best.randomize()
best.compute_cost()
for i in xrange(10000):
    indiv = Indiv()
    indiv.randomize()
    indiv.compute_cost()
    if indiv.cost < best.cost:
        best = indiv
print('Random:')
best.display()
