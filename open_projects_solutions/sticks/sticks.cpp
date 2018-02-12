#include "sticks_config.h"

int main()
{
    // the current configuration
    int sticks = 21;
    Sticks game(sticks);

    bool human_turn = true;
    int i, winner;

    while(sticks)
    {
        int max_move = std::min(sticks, 3);
        game.Print();


        if(human_turn)
        {
            auto avail = game.AvailableMoves();
            while(true)
            {
                std::cout << "Player's turn, enter a number in [1,3]: ";
                std::cin >> i;
                if(i > 0 && i <= max_move && !game.NotContains(avail, i))
                    break;
            }
        }
        else
        {
            // try to do best move
            i = (sticks - 1) % 4;
            if(i == 0)
                i = rand() % 3 + 1;
            std::cout << "Computer plays " << i << std::endl;
        }
        game.MakeMove(i);
        sticks -= i;
        human_turn = !human_turn;
    }
    if(game.Winner() == 1)
        std::cout << "Human wins" << std::endl;
    else
        std::cout << "Computer wins" << std::endl;
}
