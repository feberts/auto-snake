#include "snake_computer.h"

void Snake_computer::send(const Position & dest, const Snake & opponent)
{
    if(!pathfinder) { return; }

    Positions blocked;

    for(size_t i = 0; i < body.size(); ++i) // exclude some body positions from path finding
    {
        pathfinder->path(head(), body[i]);

        if(pathfinder->path_length() < (Distance)(body.size() - i))
        {
            blocked.push_back(body[i]);
            pathfinder->block_nodes(blocked);
        }
    }

    for(size_t i = 0; i < opponent.body.size(); ++i) // exclude some opponents body positions
    {
        pathfinder->path(head(), opponent.body[i]);

        if(pathfinder->path_length() <= (Distance)(opponent.body.size() - i))
        {
            blocked.push_back(opponent.body[i]);
            pathfinder->block_nodes(blocked);
        }
    }

    path = pathfinder->path(head(), dest);
    if(!path.empty()) { path.pop(); } // path.top() = head position
}
