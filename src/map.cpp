#include "map.h"
#include "print.h"

Map::Map(const Distance size_v, const Distance size_h)
    : size_v(size_v), size_h(size_h), pathfinder(Pathfinder(size_v, size_h, 1))
{
    init_pathfinder();
}

void Map::init_pathfinder()
{
    for(Distance v = 1; v < size_v - 1; ++v)
    {
        for(Distance h = 1; h < size_h - 1; ++h)
        {
            pathfinder.add_node(Position(v, h));
        }
    }

    for(Distance v = 1; v < size_v - 1; ++v)
    {
        for(Distance h = 1; h < size_h - 1; ++h)
        {
            if(h < size_h - 2) pathfinder.add_edge(Position(v, h), Position(v, h + 1));
            if(v < size_v - 2) pathfinder.add_edge(Position(v, h), Position(v + 1, h));
        }
    }
}

Pathfinder * Map::get_pathfinder()
{
    return &pathfinder;
}

bool Map::collision(const Position & pos) const
{
    return pos.v < 1 || pos.h < 1 || pos.v >= size_v - 1 || pos.h >= size_h - 1;
}

void Map::draw() const
{
    for(Distance h = 0; h < size_h; ++h)
    {
        print(0, h, fence); // top row
        print(size_v - 1, h, fence); // bottom row
    }

    for(Distance v = 0; v < size_v; ++v)
    {
        print(v, 0, fence); // left column
        print(v, size_h - 1, fence); // right column
    }
}
