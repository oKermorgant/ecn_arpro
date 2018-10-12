#ifndef PLAYER_H
#define PLAYER_H

#include <vector>

class Player
{
private:
    bool human;
    std::vector<int> grid;
    int &cell(int r, int c)
    {
        return grid[c + 10*r];
    }

public:
    Player(bool is_human);

    void shoot(Player other);

    void display();

    bool alive();


};

#endif // PLAYER_H
