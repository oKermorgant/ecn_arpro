import numpy as np

import random
 



class Travel:
    def __init__(self):
        self.order = list(range(Travel.n))
        self.randomize()
        
    @staticmethod
    def load(filename):
        import yaml
        data = yaml.safe_load(open(filename))
        Travel.n = len(data['cities'])
        Travel.distances = [data[v] for v in range(Travel.n)]
        Travel.cities = data['cities']

    def randomize(self):
        random.shuffle(self.order)
        self.compute_cost()
        
    def compute_cost(self):
        self.cost = 0
        for i in range(self.n):
            self.cost += self.distances[self.order[i-1]][self.order[i]]

    def __lt__(self, other):
        return self.cost < other.cost

    def __eq__(self, other):
        return self.order == other.order


    def cross_and_mutate(self, t1, t2):
        n = random.randint(1, self.n-2)
        self.order = t1.order[:n+1]
        idx = t2.order.index(t1.order[n])
        for i in range(1, self.n):
            cur = (idx + i) % self.n
            if t2.order[cur] not in self.order:
                self.order.append(t2.order[cur])
        '''
        for v in self.order:
            if self.order.count(v) != 1:
                print('!!!')
        '''
        n1 = random.randint(0, self.n-1)
        n2 = random.randint(0, self.n-1)
        self.order[n1], self.order[n2] = self.order[n2], self.order[n1]
        self.compute_cost()
        
    def display(self):
        output = ''
        for key in self.order:
            output += '{} -> '.format(self.cities[key])
        print(output + self.cities[self.order[0]])
        print('Distance: {}'.format(self.cost))

    def plot(self):
        import os
        os.system('python3 show_travel.py ' + ' '.join(str(city) for city in self.order))
