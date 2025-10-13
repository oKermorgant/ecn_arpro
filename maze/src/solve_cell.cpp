#include <a_star.h>
#include <maze.h>

using namespace std;
using namespace ecn;

// a node is a x-y position, we move from 1 each time
class Position : public Point
{
public:
    // constructor from coordinates
    Position(int _x, int _y) : Point(_x, _y) {}

    // constructor from base ecn::Point
    Position(ecn::Point p) : Point(p.x, p.y) {}

    int distToPrevious() const
    {
        // in cell-based motion, the distance to the previous node is always 1
        return 1;
    }

    std::vector<Position> neighboors() const
    {
        // this method should return  all positions reachable from this one
        std::vector<Position> generated;

        // TODO add free reachable positions from this point







        return generated;
    }
};



int main( int argc, char **argv )
{
    // load file
    // let Point know about this maze
    Position::maze.load(argc, argv);

    // initial and goal positions as Position's
    Position start = Position::maze.start(),
             goal = Position::maze.end();

    // call A* algorithm
    ecn::Astar(start, goal);

    // save final image
    Position::maze.saveSolution("cell");
    cv::waitKey(0);

}
