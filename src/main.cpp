#include "game.h"
#include "print.h"
#include <ncurses.h>
#include <time.h>

int main()
{
    srand(time(0));

    initscr();             // create empty screen
    cbreak();              // disable input buffering (no <enter> required)
    noecho();              // user input invisible (visible with echo())
    keypad(stdscr, TRUE);  // allow function and arrow keys
    nodelay(stdscr, TRUE); // do not stop at getch(), instead return ERR if no key is pressed
    curs_set(0);           // cursor invisible (visible with 1)

    print(1, 1, "SNAKE");

    Game * game;

    switch(menu(3, 1, {{'1', "Classic"}, {'2', "Battle"}}))
    {
        case '1': game = new Game_classic; break;
        case '2': game = new Game_battle;  break;
    }

    do
    {
        game->start();
        // napms(5000);
        press_any_key(MAP_SIZE_V + 4, 0, "press <space> to continue", ' ');
    }
    while(true);

    delete game;

    endwin(); // close window

    return 0;
}
