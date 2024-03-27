#include "snake.h"
#include "print.h"

Snake::Snake(const Direction dir, const Body & body, const char body_symbol, Pathfinder * pathfinder)
    : direction(dir), body(body), body_symbol(body_symbol), pathfinder(pathfinder) { }

Snake::Snake() : pathfinder(nullptr) { }

void Snake::move()
{
    if(!path.empty())
    {
        Position next = path.top();
        path.pop();

        if     (next.v > head().v) direction = Direction::down;
        else if(next.v < head().v) direction = Direction::up;
        else if(next.h > head().h) direction = Direction::right;
        else if(next.h < head().h) direction = Direction::left;
    }

    Position new_head = head();

    switch(direction)
    {
        case Direction::up:    new_head.v--; break;
        case Direction::down:  new_head.v++; break;
        case Direction::left:  new_head.h--; break;
        case Direction::right: new_head.h++; break;
        case Direction::none:  return;       break;
    }

    body.push_front(new_head);
    body.pop_back();
}

void Snake::change_direction(const Direction dir)
{
    if((int)direction + (int)dir != 3) // do not reverse direction
    {
        direction = dir;
    }
}

void Snake::grow()
{
    body.push_back(body.back());
}

const Position & Snake::head() const
{
    return body.front();
}

void Snake::send(const Position & dest)
{
    if(!pathfinder) { return; }

    Positions blocked;

    for(size_t i = 0; i < body.size(); ++i) // exclude some body positions from path finding
    {
        pathfinder->path(head(), body[i]);

        if(pathfinder->path_length() < (Distance)(body.size() - i))
        {
            blocked.push_back(body[i]);
            pathfinder->block_nodes(blocked);
        }
    }

    path = pathfinder->path(head(), dest);
    if(!path.empty()) { path.pop(); } // path.top() = head position
}

void Snake::clear_path()
{
    path = Path();
}

void Snake::kill()
{
    body_symbol = 'x';
    head_symbol[(int)Direction::none] = head_symbol[(int)direction]; // keep current symbol
    direction = Direction::none;
}

bool Snake::collision(const Position & pos) const
{
    for(size_t i = 1; i < body.size(); ++i) // exclude head
    {
        if(body[i] == pos) { return true; }
    }

    return false;
}

void Snake::draw() const
{
    draw_path();

    for(const Position & pos : body)
    {
        print(pos, body_symbol);
    }

    print(head(), head_symbol[(int)direction]);
}

void Snake::draw_path() const
{
    Path p = path;

    while(!p.empty())
    {
        print(p.top(), '.');
        p.pop();
    }
}
