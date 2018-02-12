import sys
import random

legend = ['.','x','o']

combos = [[1,2,3],[4,5,6],[7,8,9],[1,4,7],[2,5,8],[3,6,9],[1,5,9],[7,5,3]]

def PrintGrid(grid):
    for i in xrange(3):
        print ' ' + ' '.join([legend[v] for v in grid[3*i:3*(i+1)]])
        
def TestWinner(grid):    
    for player in [1,2]:
        positions = [i+1 for i in range(9) if grid[i] == player]
        
    for combo in combos:
        comb_count = 0
        for p in positions:
            if p in combo:
                comb_count += 1
        if comb_count == 3:
            if player == 1:
                print("You win!")
            else:
                print("I win!")
            sys.exit(0)        
    
    

grid = [0] * 9


while True:
    
    PrintGrid(grid)
    TestWinner(grid)                
    # ask for user choice
    while True:    
        c = input("Please enter a grid cell: ")
        if c in range(1,10):
            if grid[c-1] == 0:
                break
    grid[c-1] = 1
    
    TestWinner(grid)
        
    # computer strategy
    positions = [i+1 for i in range(9) if grid[i] == 2]
    choice = 10
    
    if len(positions) > 1:
        for combo in combos:
            comb_count = 0
            for p in positions:
                if p in combo:
                    comb_count += 1
            if comb_count == 2:
                winning = [c for c in combo if c not in positions][0]-1
                if grid[winning] == 0:
                    choice = winning
                    break
                
                
    if choice == 10:
        choice = random.choice([i for i,v in enumerate(grid) if v == 0])
                    
    grid[choice] = 2
    
    
        
        
        
    
