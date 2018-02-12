import random
import sys
import time

# if no arguments, the human tries to guess
# C++: const bool human_guess = (argc == 1);

human_guess = (len(sys.argv) == 1)

if human_guess:
    
    # srand(time(NULL));
    random.seed(time.clock)
    # const unsigned int n = rand() % 100;
    n = random.randint(1,100)
    
    while True:
        # ask the user for a number
        #    cout << "Please enter a number: ";
        #    cin >> m;
        m = input('Please enter a number (1-100): ')
        
        if m == n:
            print("That's it, congratulations")
            break
        elif m < n:
            print("Too small")
        else:
            print("Too large")

else:
    lower = 1
    upper = 100
    
    while True:
        
        # guess = 0.5*(lower + upper)
        guess = int(0.5*(lower + upper))
        
        print("   0 if ok, 1 if too small, 2 if too large")
        response = input("Is it " + str(guess) + "? - ")
        
        if response == 0:
            print(" I knew it!")
            break
        elif lower == upper:
            print("I think you are cheating")
            break
        elif response == 1:
            lower = guess +1
        else:
            upper = guess -1
