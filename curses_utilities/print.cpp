#include "print.h"
#include <cassert>

const Distance H_STRETCH = 2; // 1 = no horizontal stretching

using namespace std;

#ifndef NDEBUG
bool inside_window(const Distance v, const Distance h)
{
    int size_v, size_h;
    getmaxyx(stdscr, size_v, size_h);

    return v >= 0 && h >= 0 && v < size_v && h * H_STRETCH < size_h;
}
#endif

void print(const Distance v, const Distance h, const char c)
{
    assert(inside_window(v, h) && "cannot print outside window boundary");

    mvaddch(v, h * H_STRETCH, c);
}

void print(const Distance v, const Distance h, const string & str)
{
    assert(inside_window(v, h) && "cannot print outside window boundary");

    mvaddstr(v, h * H_STRETCH, str.c_str());
}

void print(const Position & pos, const char c)
{
    print(pos.v, pos.h, c);
}

void print(const Position & pos, const string & str)
{
    print(pos.v, pos.h, str);
}

void print2d(const Distance v, const Distance h, const string & str)
{
    assert(inside_window(v, h) && "cannot print outside window boundary");

    const Distance H = h * H_STRETCH;

    Distance row = v;
    Distance col = H;

    for(const char c : str)
    {
        if(c == '\n')
        {
            col = H;
            ++row;
            continue;
        }

        mvaddch(row, col, c);
        ++col;
    }
}

void print2d(const Position & pos, const string & str)
{
    print2d(pos.v, pos.h, str);
}

string stretch(const string & str)
{
    string stretched;
    char prev = '\n';

    for(const char c : str)
    {
        if(c != '\n' && prev != '\n')
        {
            stretched += string(H_STRETCH - 1, ' ');
        }

        stretched += c;
        prev = c;
    }

    return stretched;
}

Position click_position(const Distance clicked_v, const Distance clicked_h)
{
    return Position(clicked_v, clicked_h / H_STRETCH);
}

void get_window_size(Distance & size_v, Distance & size_h)
{
    getmaxyx(stdscr, size_v, size_h);
    size_h += H_STRETCH - 1;
    size_h /= H_STRETCH;
}

void press_any_key(const Distance v, const Distance h, const string & msg, const char key)
{
    print(v, h, msg);
    flushinp();
    if(key == ERR) { while(key == getch()) { napms(10); } }
    else           { while(key != getch()) { napms(10); } }
    flushinp();
}

char menu(Distance v, const Distance h, const map<char, string> & menu_entries)
{
    for(const auto & [key, description] : menu_entries)
    {
        print(v++, h, string(1, key) + " - " + description);
    }

    char input;

    do
    {
        input = getch();
        napms(10);
    }
    while(!menu_entries.count(input));

    return input;
}

void quit()
{
    endwin();
    exit(0);
}
