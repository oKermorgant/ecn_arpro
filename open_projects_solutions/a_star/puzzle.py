#!/usr/bin/env python

import sys,os
from pylab import sqrt, rand
from time import time
from multiprocessing import Pool

class Node:
    n = 0
    n2n = 0
    n2 = 0
    def __init__(self, tag = 0, zero_pos = 0, parent = None):        
        if tag != 0:
            self.build_from(tag)
        self.parent = parent
        self.cost = None

        # build family tags
        if parent != None:
            self.set_parent(parent)
        else:
            self.g = 0
            self.family_tags = []
            
    def set_parent(self, parent):
        self.g = parent.g + 1
        self.family_tags = self.parent.family_tags + [self.parent.tag]
            
    def compute_h(self, goal):
        self.h = sum([self.tag[i] == goal.tag[i] for i in xrange(len(self.tag))])
        self.h = sum([abs(self.i[k]-goal.i[k]) + abs(self.j[k]-goal.j[k]) for k in xrange(self.n2)])
        
    def compute_f(self):
        self.f = self.g + self.h

    def build_from(self, code):
        self.tag = code
        self.zero_pos = code.index(0)
        self.i = [self.tag.index(i)/self.n for i in xrange(self.n**2)]
        self.j = [self.tag.index(i) % self.n for i in xrange(self.n**2)]
                
    def print_tree(self):
        if self.parent != None:
            self.parent.print_tree()
            print ''
            # computes and prints transition if any parent 
            zero_change = self.zero_pos - self.parent.zero_pos 
            move = 'left'
            if zero_change == -1:
                move = 'right'
            elif zero_change == self.n:
                move = 'up'
            elif zero_change == -self.n:
                move = 'down'
            print self.parent.tag[self.zero_pos], move
        # prints the grid
        self.display()
                   
    def display(self):
        # print grid        
        l = len(str(self.n**2-1))
        tag_str = [' '*(l-len(str(i))) + str(i) for i in self.tag]
        print '-'*(self.n+1+self.n*l)
        for i in xrange(self.n):
            print '|' + '|'.join([tag_str[self.n*i+j] for j in xrange(self.n)]) + '|'
            if i != self.n-1:
                print '|' + '+'.join(['-'*l for j in xrange(self.n)]) + '|'
        print '-'*(self.n+1+self.n*l)

        #print self.transition                
        
    def random_tree(self, depth = 0):
        if rand() < 0.1:
            print 'Returned random child with depth of', depth
            return Node(self.tag, self.tag.index(0))
        children = self.children()
        return children[int(rand()*len(children))].random_tree(depth+1)
        
    def children(self):
        children = []
        mod = self.zero_pos % self.n
        parent_zero_pos = -1
        if self.parent != None:
            parent_zero_pos = self.parent.zero_pos
        
        if mod != 0 and parent_zero_pos != self.zero_pos-1:                        # zero can go left (-1)
            tag = [t for t in self.tag]
            tag[self.zero_pos] = tag[self.zero_pos-1]
            tag[self.zero_pos-1] = 0
            if tag not in self.family_tags:
                children.append(Node(tag, self.zero_pos-1, self))
            
        if mod != self.n-1 and parent_zero_pos != self.zero_pos+1:                 # zero can go right (+1)
            tag = [t for t in self.tag]
            tag[self.zero_pos] = tag[self.zero_pos+1]
            tag[self.zero_pos+1] = 0
            if tag not in self.family_tags:
                children.append(Node(tag, self.zero_pos+1, self))
            
        if self.zero_pos >= self.n and parent_zero_pos != self.zero_pos-self.n:         # zero can go up (-n)
            tag = [t for t in self.tag]
            tag[self.zero_pos] = tag[self.zero_pos-self.n]
            tag[self.zero_pos-self.n] = 0
            if tag not in self.family_tags:
                children.append(Node(tag, self.zero_pos-self.n, self))            
            
        if self.zero_pos < self.n2n and parent_zero_pos != self.zero_pos+self.n:        # zero can go down (+n)
            tag = [t for t in self.tag]
            tag[self.zero_pos] = tag[self.zero_pos+self.n]
            tag[self.zero_pos+self.n] = 0
            if tag not in self.family_tags:
                children.append(Node(tag, self.zero_pos+self.n, self))                                    
        return children
        
    def __eq__(self, other):
        return self.tag == other.tag    
                     

def find_bruteforce(start, goal, depth = 1):
    # check first call
    if type(start) != list:
        start = [start]
       
    # check for goal in given starts
    for candidate in start:
        if goal == candidate:
            return candidate

    # build new generation
    all_children = [node.children() for node in start]
    children = all_children[0]
    for other_children in all_children[1:]:
        children += [child for child in other_children if child not in children]
    
    print 'Examining depth', depth, 'with', len(children), 'candidates'
    return find_bruteforce(children, goal, depth+1)


def find_astart(start, goal):
    closedset = []              # The set of nodes already evaluated.
    openset = [start]           # The set of tentative nodes to be evaluated, initially containing the start node
    start.compute_h(goal)
    start.compute_f()
    
    t = time()
    
    it = 0
    while len(openset) != 0:
        it += 1
        # current <- best of openset
        costs = [node.f for node in openset]
        current = openset[costs.index(min(costs))]
        # if goal was found, return this element
        if goal == current:
            print 'Found in', time()-t, 'sec'
            return current
        # move current from openset to closedset
        closedset.append(current)
        openset.remove(current)
        
        for child in current.children():
            union = openset + closedset
            add_child = False
            if child in union:
                twin = union[union.index(child)]
                if twin.g > child.g:
                    twin.set_parent(current)
                    twin.compute_f()
                    openset.append(twin)
            else:
                child.compute_h(goal)
                child.compute_f()
                openset.append(child)
        #print 'Depth', it, len(openset), 'candidates'
        
        
if __name__ == '__main__':
    global found
    found = False
    if len(sys.argv) < 1:
        print 'Give a problem file'
        sys.exit(0)
        
    if not os.path.lexists(sys.argv[1]):
        print 'File', sys.argv[1], 'does not exist'
        sys.exit(0)        
        
    with open(sys.argv[1]) as f:
        lines = f.read().splitlines()
        idx = -1
        parsed = ['','']
        try:
            # parse file
            for line in lines:
                if 'start' in line:
                    idx = 0
                elif 'goal' in line:
                    idx = 1
                elif idx in (0,1):
                    parsed[idx] += ' ' + line
                    
            # str to int
            for k in (0,1):
                parsed[k] = [int(v) for v in parsed[k].split()]
            # get puzzle dimension
            Node.n = int(sqrt(len(parsed[1])))
            if Node.n**2 != len(parsed[1]):
                print 'Goal grid is not a square'
                sys.exit(0)                
            Node.n2n = Node.n**2 - Node.n
            Node.n2 = Node.n**2
            # build goal node
            goal = Node()
            goal.build_from(parsed[1])
            
            # check starting data
            if len(parsed[0]) != len(parsed[1]):
                # seems odd, no grid? build one
                print 'No valid start grid found, using random'
                start = goal.random_tree()
            else:
                start = Node()
                start.build_from(parsed[0])
        except:
            print 'Problem while parsing'
            print 'Define goal grid. Define start grid or use a random (valid) grid.'
            
    t = time()
    #path = find_bruteforce(start, goal)
    #print 'Found in', time()-t, 'sec'
    path = find_astart(start, goal)
    print 'Path length found:', path.g, '- press [Enter] to display sequence'
    a = raw_input('')
    path.print_tree()
