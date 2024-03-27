#ifndef PATHFINDER_H
#define PATHFINDER_H

#include "graph.h"
#include "position.h"

typedef std::stack<Position> Path;
typedef std::vector<Position> Positions;

class Pathfinder : private graph::Graph
{
public:

    Pathfinder(const Distance map_size_v, const Distance map_size_h, const Distance padding = 0);

    void add_node(const Position & pos);
    void add_edge(const Position & first, const Position & second, const Distance dist = 1);
    void add_directed_edge(const Position & src, const Position & dest, const Distance dist = 1);

    Path path(const Position & src, const Position & dest);
    Distance path_length() const;

    void block_nodes(const Positions & positions);

private:

    const Distance m_map_size_v;
    const Distance m_map_size_h;
    const Distance m_padding;

    Position to_position(const graph::Node_id id) const;
    graph::Node_id to_id(const Position & pos) const;
};

#endif // PATHFINDER_H
