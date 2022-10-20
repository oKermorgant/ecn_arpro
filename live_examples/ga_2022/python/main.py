#!/usr/bin/env python3
from time import time
from travel import Travel

from ga import ga

Travel.load('../tsp.yaml')

start = time()

best = ga(Travel)

print(f'Took {1000*(time()-start)} ms')

best.display()
best.plot()
