#include "pathfinder.h"
#include <cassert>
#include <deque>

#ifndef NDEBUG
bool on_map(const Position & pos, const Distance map_size_v,
            const Distance map_size_h, const Distance padding)
{
    return pos.v >= 0 + padding
        && pos.h >= 0 + padding
        && pos.v < map_size_v - padding
        && pos.h < map_size_h - padding;
}
#define ON_MAP_ARGS m_map_size_v, m_map_size_h, m_padding
#endif

Pathfinder::Pathfinder(const Distance map_size_v, const Distance map_size_h, const Distance padding)
    : m_map_size_v(map_size_v), m_map_size_h(map_size_h), m_padding(padding)
{
    assert(map_size_v > 0 && map_size_h > 0 && "map size must be > 0");
    assert(padding >= 0 && "padding must not be < 0");
}

void Pathfinder::add_node(const Position & pos)
{
    assert(on_map(pos, ON_MAP_ARGS) && "node outside map");

    Graph::add_node(to_id(pos));
}

void Pathfinder::add_edge(const Position & first, const Position & second, const Distance dist)
{
    assert(on_map(first, ON_MAP_ARGS) && "first node outside map");
    assert(on_map(second, ON_MAP_ARGS) && "second node outside map");

    Graph::add_edge(to_id(first), to_id(second), dist);
}

void Pathfinder::add_directed_edge(const Position & src, const Position & dest, const Distance dist)
{
    assert(on_map(src, ON_MAP_ARGS) && "src node outside map");
    assert(on_map(dest, ON_MAP_ARGS) && "dest node outside map");

    Graph::add_directed_edge(to_id(src), to_id(dest), dist);
}

Path Pathfinder::path(const Position & src, const Position & dest)
{
    assert(on_map(src, ON_MAP_ARGS) && "src node outside map");
    assert(on_map(dest, ON_MAP_ARGS) && "dest node outside map");

    graph::Path path = Graph::path(to_id(src), to_id(dest));

    std::deque<Position> steps;

    while(!path.empty())
    {
        steps.push_front(to_position(path.top()));
        path.pop();
    }

    return Path(steps);
}

Distance Pathfinder::path_length() const
{
    return Graph::path_length();
}

void Pathfinder::block_nodes(const Positions & positions)
{
    graph::Node_ids ids;

    for(const Position & pos : positions)
    {
        assert(on_map(pos, ON_MAP_ARGS) && "node outside map");

        ids.push_back(to_id(pos));
    }

    Graph::block_nodes(ids);
}

Position Pathfinder::to_position(const graph::Node_id id) const
{
    return Position(id / m_map_size_h, id % m_map_size_h);
}

graph::Node_id Pathfinder::to_id(const Position & pos) const
{
    return pos.v * m_map_size_h + pos.h;
}
