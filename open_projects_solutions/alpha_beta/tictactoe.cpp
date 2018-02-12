#include <algorithm>
#include <vector>
#include "tictactoe_config.h"
#include "alpha_beta_game.h"

int main()
{
    AlphaBetaGame<TicTacToe>(true,false,2); // human vs computer, AI looks 4 turns ahead
}
