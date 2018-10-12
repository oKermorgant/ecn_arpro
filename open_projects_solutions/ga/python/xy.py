import numpy as np
 
class XY:
    def __init__(self):
        pass
        
    def randomize(self):
        self.x = np.random.uniform(-5,5)
        self.y = np.random.uniform(-5,5)
        
    def compute_cost(self):
        self.cost = 20 + self.x**2 + self.y**2 - 10*(np.cos(2*np.pi*self.x) + np.cos(2*np.pi*self.y))
        
    def cross_and_mutate(self, xy1, xy2):
        a = np.random.uniform(0,1)
        self.x = np.clip( a*xy1.x + (1-a)*xy2.x + np.random.uniform(-0.2, 0.2), -5, 5)
        self.y = np.clip( a*xy1.y + (1-a)*xy2.y + np.random.uniform(-0.2, 0.2), -5, 5)
        
    def display(self):
        print('({}, {}): {}'.format(self.x, self.y, self.cost))
