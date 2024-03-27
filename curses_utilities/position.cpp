#include "position.h"

bool Position::operator==(const Position & other) const
{
    return v == other.v && h == other.h;
}

bool Position::operator!=(const Position & other) const
{
    return !(*this == other);
}
