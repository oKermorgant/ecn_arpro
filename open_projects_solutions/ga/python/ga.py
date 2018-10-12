from copy import deepcopy
import random

def nth_element(population, k):
    for i in xrange(k):
        idx = population[i:].index(min(population[i:], key=lambda indiv: indiv.cost))
        population[i],population[i+idx] = population[i+idx],population[i]
        
def ga(Indiv):
    
    n = 500
    max_iter = 100
    keep = 10
    max_same = 30
    
    population = [Indiv() for k in xrange(n)]
    for indiv in population:
        indiv.randomize()
        indiv.compute_cost()
        
    new_pop = [Indiv() for k in xrange(n/2)]
        
    iterations = 0
    same = 0
    
    nth_element(population, keep)
    best = population[0]        
    
    while iterations < max_iter and same < max_same:
        iterations += 1
        
        # elitism
        new_pop[:keep] = population[:keep]
        
        # tournament
        for k in xrange(keep, n/2):
            n1 = random.randint(0, n-1)
            n2 = random.randint(0, n-1)
            while n1 == n2:
                n2 = random.randint(0, n-1)
            if population[n1].cost < population[n2].cost:
                new_pop[k] = deepcopy(population[n1])
            else:
                new_pop[k] = deepcopy(population[n2])
                
        # crossing
        population[:n/2] = new_pop
        for k in xrange(n/2, n):
            n1 = random.randint(0, n/2-1)
            n2 = random.randint(0, n/2-1)
            while n1 == n2:
                n2 = random.randint(0, n/2-1) 
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
        
        
