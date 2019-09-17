#include <algorithm>
#include <vector>
#include "four_in_a_row_config.h"
#include "alpha_beta_game.h"

int main()
{
    AlphaBetaGame<FourInARow>(true, false, 5);  // human vs computer, AI looks 6 turns ahead
}
