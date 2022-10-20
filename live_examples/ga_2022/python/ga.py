from copy import deepcopy
import random

def nth_element(population, k):
    population.sort()
    return
    for i in range(k):
        idx = population[i:].index(min(population[i:]))
        population[i],population[i+idx] = population[i+idx],population[i]

def differentRandom(low, high):
    n1 = random.randint(low, high)
    n2 = random.randint(low, high-1)
    if n1 == n2:
        return (n1, n2+1)
    return (n1,n2)
        

def reorder(population, keep_best):
    nth_element(population, keep_best)
    return min(population[:keep_best])


def ga(Indiv):

    pop_size = 500
    keep_best = 30
    max_iter = 100
    max_iter_seq = 30

    population = [Indiv() for _ in range(pop_size)]
    winners = [Indiv() for _ in range(pop_size//2-keep_best)]
    best = reorder(population, keep_best)

    iters = 0
    iter_seq = 0
    best_cost = best.cost

    while iters < max_iter and iter_seq < max_iter_seq:

        for winner in range(len(winners)):
            n1,n2 = differentRandom(0, pop_size-1)
            winners[winner] = min(population[n1], population[n2])

        population[keep_best:pop_size//2] = deepcopy(winners)

        for crossed in population[pop_size//2:]:
            n1,n2 = differentRandom(0, pop_size//2-1)
            crossed.cross_and_mutate(population[n1], population[n2])

        best = reorder(population, keep_best)

        if best_cost > best.cost:
            best_cost = best.cost
            iter_seq = 0
        else:
            iter_seq += 1

        iters += 1

    return best

        
        
