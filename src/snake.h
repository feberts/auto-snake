#ifndef SNAKE_H
#define SNAKE_H

#include "map.h"
#include "pathfinder.h"
#include "position.h"
#include <deque>
#include <vector>

enum class Direction : int { up = 0, left = 1, right = 2, down = 3, none = 4 };

struct Snake
{
    typedef std::deque<Position> Body;

    Direction direction;
    Body body;
    char body_symbol;
    std::vector<char> head_symbol = {'^', '<', '>', 'v', 's'};
    Pathfinder * pathfinder;
    Path path;

    Snake();
    Snake(const Direction dir, const Body & body, const char body_symbol,
          Pathfinder * pathfinder = nullptr);

    void move();
    void change_direction(const Direction dir);
    void grow();
    const Position & head() const;
    void send(const Position & dest);
    void clear_path();
    void kill();
    bool collision(const Position & pos) const;
    void draw() const;
    virtual void draw_path() const;
};

#endif // SNAKE_H
