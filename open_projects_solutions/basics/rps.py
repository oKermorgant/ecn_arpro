import random
import sys
import time

random.seed(time.clock())
#  vector<string> RPS = {"r", "p", "s"};
rps = ('r','p','s')
#  vector<string> RPS2 = {"rock", "paper", "scissors"};
rps2 = ('rock','paper','scissors')


while True:
    
    p = ''
    while p not in rps:
        p = raw_input("Type r (Rock), p (Paper) or s (Scissors): ")
        
    # find corresponding index
    # human = distance(RPS.begin(), find(RPS.begin(),RPS.end(),rps));
    human = rps.index(p)
    
    # random number for computer
    ai = random.randint(0,2)
    choice = str(rps2[ai])
    
    # compare
    ai = (human - ai + 3) % 3
    
    if ai == 0:
        msg = "Draw"
    elif ai == 1:
        msg = "You win!"
    else:
        msg = "I win!"
        
    print("I went for " + choice + ": " + msg)
