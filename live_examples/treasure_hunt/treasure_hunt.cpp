#include <duels/treasure_hunt/game.h>
#include "treasure_hunt_ai.h"

using namespace duels::treasure_hunt;

int main(int argc, char** argv)
{
  const std::string my_name = "your name";

  // AI level can be
  // - 0 (does not move)
  // - 1 (moves randomly)
  // - 2 (tries to always approach the goal)
  // - 3 (uses the proposed algorithm)
  Game game(argc, argv, my_name, 1);    // to play as player 1 against level 1 AI
  //Game game(argc, argv, my_name, -2);    // to play as player 2 against level 2 AI

  Input input;
  Feedback feedback;
  [[maybe_unused]] const auto timeout = game.timeout_ms();

  TreasureHuntAI ai;

  while(game.get(feedback))
  {
    // write input in less than timeout
    input.action = ai.computeFrom(feedback);

    game.send(input);
  }
}
