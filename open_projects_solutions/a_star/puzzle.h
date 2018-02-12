#ifndef PUZZLE_H
#define PUZZLE_H

#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <vector>

// what is this puzzle
class Puzzle
{
public:
    // default constructor
    Puzzle()
    {
        grid.resize(n*n,0);
        // build the desired configuration
        for(unsigned int i=0;i<n*n-1;++i)
            grid[i] = i+1;

        // where the 0 is
        c0 = n*n-1;
    }

    void randomize(int random_moves = 40)
    {
        // randomize
        srand(clock());
        std::vector<unsigned int> all_moves;

        for(int i=0;i<random_moves;++i)
        {
            all_moves = gen_moves();
            int idx = rand() % all_moves.size();
            std::iter_swap(grid.begin()+c0, grid.begin()+all_moves[idx]);
            c0 = all_moves[idx];
        }
    }

    Puzzle(Puzzle *parent, unsigned int _c0)
    {
        grid = parent->grid;
        c0 = _c0;
        std::iter_swap(grid.begin()+c0, grid.begin()+parent->c0);
    }


    void print(Puzzle* parent)
    {
        if(parent)
        {
            // print the move to go from parent to this
            int diff = c0 - parent->c0;
            std::cout << std::endl << grid[parent->c0];
            if(diff == -1)
                std::cout << " right";
            else if(diff == 1)
                std::cout << " left";
            else if(diff == n)
                std::cout << " up";
            else
                std::cout << " down";
            std::cout << std::endl;
        }
        for(unsigned int i=0;i<n;++i)
        {
            for(unsigned int j=0;j<n;++j)
            {
                if(grid[n*i+j])
                std::cout << grid[n*i+j] << " ";
                else
                    std::cout << ". ";
            }
            std::cout << std::endl;
        }
    }



    bool is(Puzzle * goal_ptr)
    {
        for(int i=0;i<n*n-1;++i)
        {
            if(grid[i] != goal_ptr->grid[i])
                return false;
        }
        return true;
    }

    std::vector<unsigned int> gen_moves()
    {
        std::vector<unsigned int> moves;

        if(c0 > n)                  // up-move with c0 - n
            moves.push_back(c0-n);

        if(c0 < n*n-n)              // down move with c0 + n
            moves.push_back(c0+n);

        if(c0 % n != 0)             // left move with c0 -1
            moves.push_back(c0-1);

        if(c0 % n != n-1)           // right move with c0+1
            moves.push_back(c0+1);
        return moves;
    }

    void children(std::vector<Puzzle* > &children)
    {
        children.clear();
      //  std::cout << "Creating children of " << c0 << "... ";
        for(auto c: gen_moves())
        {
            children.push_back(new Puzzle(this, c));
         //   std::cout << c << " ";
        }
       // std::cout << std::endl;
    }

    int h(const Puzzle &goal)
    {
        // distance to final puzzle
        int h = 0;
        int idx, idx_goal, r, c;
        for(unsigned int i=1;i<n*n-1;++i)
        {
            // where this number is in the grid
            idx = std::distance(grid.begin(), std::find(grid.begin(), grid.end(), i));
            // where it is in the goal
            idx_goal = std::distance(goal.grid.begin(), std::find(goal.grid.begin(), goal.grid.end(), i));

            // in terms of row x cols and difference with where it should be
            r = idx / n - idx_goal/n;
            c = idx % n - idx_goal%n;

            h += abs(r) + abs(c);
        }
        return h;
    }

    int distToParent() {return 1;}

protected:
    std::vector<unsigned int> grid;
    Puzzle* parent;
    static unsigned int n;
    unsigned int c0;
};

#endif // PUZZLE_H
