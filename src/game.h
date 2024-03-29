#ifndef GAME_H
#define GAME_H

#include "apple.h"
#include "snake_computer.h"
#include "map.h"
#include "position.h"
#include "print.h"
#include "snake.h"
#include <deque>
#include <vector>

const Distance MAP_SIZE_V = 10;
const Distance MAP_SIZE_H = 15;
const int SNAKE_BREAK = 400; // milliseconds
const char SNAKE_SYMBOL = 'o';
const char COMPUTER_SYMBOL = '*';

using namespace std;

struct Game
{
    virtual void start() = 0;
    virtual ~Game() { }
};

struct Game_classic : Game
{
    Map map = Map(MAP_SIZE_V, MAP_SIZE_H);
    Apple apple;
    Snake snake;
    bool auto_mode = false;

    void start() override
    {
        bool game_over = false;

        create_apple();
        snake = Snake(Direction::right, {{4, 4}, {4, 3}, {4, 2}}, SNAKE_SYMBOL, map.get_pathfinder());
        if(auto_mode) { snake.send(apple.position); }

        update_screen();

        while(!game_over)
        {
            // flushinp(); // flush input buffer
            napms(SNAKE_BREAK); // pause (milliseconds)
            int input = getch(); // read input

            switch(input)
            {
                case KEY_UP:    snake.change_direction(Direction::up); break;
                case KEY_DOWN:  snake.change_direction(Direction::down); break;
                case KEY_LEFT:  snake.change_direction(Direction::left); break;
                case KEY_RIGHT: snake.change_direction(Direction::right); break;
                case 'a':
                    if(auto_mode) { snake.clear_path(); }
                    else { snake.send(apple.position); }
                    auto_mode = !auto_mode;
                    break;
                case 'q':
                    quit();
                    break;
            }

            snake.move();

            if(map.collision(snake.head()) || snake.collision(snake.head()))
            {
                snake.kill();
                game_over = true;
            }

            if(apple.collision(snake.head()))
            {
                snake.grow();
                create_apple();
                if(auto_mode) { snake.send(apple.position); }
            }

            update_screen();
        }
    }

    void create_apple()
    {
        vector<Position> vacant;

        for(Distance v = 1; v < map.size_v - 1; ++v)
        {
            for(Distance h = 1; h < map.size_h - 1; ++h)
            {
                const Position pos(v, h);

                if(!snake.collision(pos) && snake.head() != pos)
                {
                    vacant.push_back(pos);
                }
            }
        }

        if(vacant.empty()) { return; } // no free positions left

        apple.position = vacant[rand() % vacant.size()];
    }

    void print_score() const
    {
        print(map.size_v + 1, 0, "Score: " + to_string(snake.body.size()));
    }

    void update_screen() const
    {
        erase(); // clear screen

        map.draw();
        snake.draw();
        apple.draw();
        print_score();

        refresh(); // update screen
    }
};

struct Game_battle : Game
{
    Map map = Map(MAP_SIZE_V, MAP_SIZE_H);
    Apple apple;
    Snake_computer snake;
    Snake_computer snake_computer;
    bool auto_mode = false;

    void start() override
    {
        bool game_over = false;

        create_apple();

        snake = Snake_computer(Direction::right, {{4, 4}, {4, 3}, {4, 2}}, SNAKE_SYMBOL, map.get_pathfinder());
        snake_computer = Snake_computer(Direction::none, {{5, 4}, {5, 3}, {5, 2}}, COMPUTER_SYMBOL, map.get_pathfinder());

        update_screen();

        while(!game_over)
        {
            // flushinp(); // flush input buffer
            napms(SNAKE_BREAK); // pause (milliseconds)
            int input = getch(); // read input

            switch(input)
            {
                case KEY_UP:    snake.change_direction(Direction::up); break;
                case KEY_DOWN:  snake.change_direction(Direction::down); break;
                case KEY_LEFT:  snake.change_direction(Direction::left); break;
                case KEY_RIGHT: snake.change_direction(Direction::right); break;
                case 'a':
                    if(auto_mode) { snake.clear_path(); }
                    auto_mode = !auto_mode;
                    break;
                case 'q':
                    quit();
                    break;
            }

            // player snake:

            if(auto_mode) { snake.send(apple.position, snake_computer); }
            snake.move();

            if(map.collision(snake.head())
                || snake.collision(snake.head())
                || snake_computer.collision(snake.head())
                || snake.head() == snake_computer.head())
            {
                snake.kill();
                break;
            }

            if(apple.collision(snake.head()))
            {
                snake.grow();
                create_apple();
            }

            // computer snake:

            snake_computer.send(apple.position, snake);
            snake_computer.move();

            if(map.collision(snake_computer.head())
                || snake_computer.collision(snake_computer.head())
                || snake.collision(snake_computer.head())
                || snake.head() == snake_computer.head())
            {
                snake_computer.kill();
                break;
            }

            if(apple.collision(snake_computer.head()))
            {
                snake_computer.grow();
                create_apple();
            }

            update_screen();
        }

        update_screen();
    }

    void create_apple()
    {
        vector<Position> vacant;

        for(Distance v = 1; v < map.size_v - 1; ++v)
        {
            for(Distance h = 1; h < map.size_h - 1; ++h)
            {
                const Position pos(v, h);

                if(!snake.collision(pos) && snake.head() != pos
                   && !snake_computer.collision(pos) && snake_computer.head() != pos)
                {
                    vacant.push_back(pos);
                }
            }
        }

        if(vacant.empty()) { return; } // no free positions left

        apple.position = vacant[rand() % vacant.size()];
    }

    void print_score() const
    {
        print(map.size_v + 1, 0, "   Human (" + string(1, SNAKE_SYMBOL) + "): " + to_string(snake.body.size()));
        print(map.size_v + 2, 0, "Computer (" + string(1, COMPUTER_SYMBOL) + "): " + to_string(snake_computer.body.size()));
    }

    void update_screen() const
    {
        erase(); // clear screen

        map.draw();
        snake_computer.draw();
        snake.draw();
        apple.draw();
        print_score();

        refresh(); // update screen
    }
};

#endif // GAME_H
