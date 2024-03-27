#ifndef MAP_H
#define MAP_H

#include "pathfinder.h"
#include "position.h"

struct Map
{
    const Distance size_v;
    const Distance size_h;
    const char fence = '#';
    Pathfinder pathfinder;

    Map(const Distance size_v, const Distance size_h);

    void init_pathfinder();
    Pathfinder * get_pathfinder();
    bool collision(const Position & pos) const;
    void draw() const;
};

#endif // MAP_H
