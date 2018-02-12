#include <algorithm>
#include <vector>
#include <iostream>


/* This function uses alpha-beta algorithm for a given game configuration
 */

template<class T>
int alpha_beta(T& game, int alpha, int beta, unsigned int recur, unsigned int max_recur)
{
    if(recur == 0)
    {
        auto choices = game.AvailableMoves();
        choices.clear();
        int val;
        for(auto move: game.AvailableMoves())
        {
            game.MakeMove(move);
            val = -alpha_beta(game, alpha, beta, 1, max_recur);
            std::cout << "Move " << move << " -> score = " << val << std::endl;
            game.CancelMove(move);
            if(val > alpha)
            {
                alpha = val;
                choices = {move};
            }
            else if(val == alpha)
                choices.push_back(move);
        }
        unsigned int idx = rand() % choices.size();
        std::cout << "Making move " << choices[idx] << std::endl;
        game.MakeMove(choices[idx]);
        return 0;
    }


    // check for end of game
    int win = game.Winner();
    if(win)
        return -100+recur;

    // what to return
    if(game.Over() || recur == max_recur)
        return recur;

    // build new moves
    int val, best = -5000;

    for(auto move: game.AvailableMoves())
    {
        game.MakeMove(move);
        val = -alpha_beta(game, -beta, -alpha, recur+1, max_recur);
        game.CancelMove(move);
        if(val > best)
        {
            best = val;
            if(best > alpha)
            {
                alpha = best;
                if(alpha > beta)
                    return best;
            }
        }
    }
    return best;
}
