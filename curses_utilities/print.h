#ifndef PRINT_H
#define PRINT_H

#include "position.h"
#include <map>
#include <ncurses.h>
#include <string>

void print(const Distance v, const Distance h, const char c);
void print(const Distance v, const Distance h, const std::string & str);
void print(const Position & pos, const char c);
void print(const Position & pos, const std::string & str);

void print2d(const Distance v, const Distance h, const std::string & str);
void print2d(const Position & pos, const std::string & str);

std::string stretch(const std::string & str);

Position click_position(const Distance clicked_v, const Distance clicked_h);
void get_window_size(Distance & size_v, Distance & size_h);

void press_any_key(const Distance v = 0, const Distance h = 0, const std::string & msg = "press any key to continue", const char key = ERR);
char menu(Distance v, const Distance h, const std::map<char, std::string> & menu_entries);

void quit();


#endif // PRINT_H
