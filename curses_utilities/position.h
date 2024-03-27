#ifndef POSITION_H
#define POSITION_H

typedef int Distance;

struct Position
{
    Distance v;
    Distance h;

    Position(const Distance v = 0, const Distance h = 0) : v(v), h(h) { }

    bool operator==(const Position & other) const;
    bool operator!=(const Position & other) const;
};

#endif // POSITION_H
