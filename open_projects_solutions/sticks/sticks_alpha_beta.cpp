#include <algorithm>
#include <vector>
#include "../alpha_beta/alpha_beta_game.h"
#include "sticks_config.h"

int main()
{
    AlphaBetaGame<Sticks>(true, false, 10);  // human vs computer, AI looks 6 turns ahead
}
