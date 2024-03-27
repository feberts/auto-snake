#ifndef SNAKE_COMPUTER_H
#define SNAKE_COMPUTER_H

#include "snake.h"

struct Snake_computer : public Snake
{
    Snake_computer(const Direction dir, const Body & body,
                   const char body_symbol, Pathfinder * pathfinder = nullptr)
        : Snake(dir, body, body_symbol, pathfinder) { }

    Snake_computer() : Snake() { }

    void send(const Position & dest, const Snake & opponent);
    void draw_path() const override { }
};

#endif // SNAKE_COMPUTER_H
