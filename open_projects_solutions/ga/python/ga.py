from copy import deepcopy
import random

def nth_element(population, k):
    population.sort()
    return
    for i in range(k):
        idx = population[i:].index(min(population[i:]))
        population[i],population[i+idx] = population[i+idx],population[i]

def differenRandom(low, high):
    n1 = random.randint(low, high)
    n2 = random.randint(low, high-1)
    if n1 == n2:
        return (n1, n2+1)
    return (n1,n2)
        
def ga(Indiv):
    
    n = 500
    max_iter = 100
    keep = 10
    max_same = 30
    
    population = [Indiv() for k in range(n)]
    for indiv in population:
        indiv.randomize()
        indiv.compute_cost()

    winners = [Indiv() for k in range(n//2-keep)]
        
    iterations = 0
    same = 0
    
    nth_element(population, keep)
    best = population[0]        
    
    while iterations < max_iter and same < max_same:
        iterations += 1
        
        # tournament
        for k in range(keep, n//2):
            n1, n2 = differenRandom(0, n-1)
            winners[k-keep] = min(population[n1], population[n2])
                
        # crossing
        population[keep:n//2] = deepcopy(winners)
        for k in range(n//2, n):
            n1,n2 = differenRandom(0, n//2-1)
            population[k].cross_and_mutate(population[n1], population[n2])
            population[k].compute_cost()
        
        nth_element(population, keep)
        new_best = population[0] 
        
        if new_best.cost == best.cost:
            same += 1
        else:
            best = new_best
            same = 0
    return best
        
        
