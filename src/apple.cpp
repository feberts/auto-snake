#include "apple.h"
#include "print.h"

bool Apple::collision(const Position & pos) const
{
    return position == pos;
}

void Apple::draw() const
{
    print(position, '@');
}
