#ifndef AB_GAME_H
#define AB_GAME_H


#include <algorithm>
#include <vector>
#include "alpha_beta.h"

// This function is a generic alpha-beta game using a given game configuration
// p1 starts.
template <class T> void AlphaBetaGame(bool p1_human = true, bool p2_human = false, unsigned int max_recur = 5)
{
    srand (clock());
    T game;
    std::vector<bool> is_human = {p1_human, p2_human};
    int a, b;
    game.GetAlphaBeta(a,b);

    int player = 1;
    // continue until there is a winner or the game is over
    while(!game.Winner() && !game.Over())
    {
        if(is_human[player-1])
        {
            game.Print();
            game.HumanInput(player);
        }
        else if (game.MustThink())
            alpha_beta(game, a, b, 0, 2*max_recur);

        // player -> other player
        player = 3-player;
    }
    game.Print();

    int win = game.Winner();
    if(win)
        std::cout << "Player " << win << " wins" << std::endl;
    else
        std::cout << "Draw" << std::endl;


}

#endif
