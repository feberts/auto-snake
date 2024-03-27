#ifndef APPLE_H
#define APPLE_H

#include "position.h"

struct Apple
{
    Position position;

    bool collision(const Position & pos) const;
    void draw() const;
};

#endif // APPLE_H
