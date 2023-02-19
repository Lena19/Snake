// Snake.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <conio.h>
#include <iostream>
#include <vector>
#include <Windows.h>
#include "Console_field.h"
#include <ctime>
#include <random>
#include "Snake.h"
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

const int WIDTH = 20;
const int HEIGHT = 20;
int initial_sleep_timer = 300, sleep_timer = 300;

mutex mtx;

void set_window() {
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, WIDTH * 17, HEIGHT * 15, true);
}

Field* create_field() {
    Field* field(new Console_field(WIDTH - 3, HEIGHT - 1));
    return field;
}

Snake set_snake(Field* f) {
    int head_posx = rand() % (WIDTH / 2) + 1;
    int head_posy = rand() % (HEIGHT / 2) + 1;
    Cell* head_cell = new Console_cell;
    return Snake(head_posx, head_posy, f, head_cell);
}

void set_field(Field*& f, Snake & s) {
    f = create_field();
    int head_posx = rand() % (WIDTH / 2) + 1;
    int head_posy = rand() % (HEIGHT / 2) + 1;
    Cell* head_cell = new Console_cell;
    s = set_snake(f);
    while (!f->spawn_target());
    sleep_timer = initial_sleep_timer;
}

void play(Snake &snake, Field* field) {
    auto start_time = chrono::high_resolution_clock::now();
    while (1) {
        field->draw();     
        //unique_lock<mutex> lck(mtx);
        if (!snake.move()) {
            set_field(field, snake);
            start_time = chrono::high_resolution_clock::now();
        }
        //lck.unlock();
        auto cur_time = chrono::high_resolution_clock::now();
        if (chrono::duration_cast<chrono::seconds>(cur_time - start_time) >= chrono::seconds(10)) {
            start_time = cur_time;
            sleep_timer = max(sleep_timer - 20, 20);
        }
        Sleep(sleep_timer);
        system("cls");
    }
}

void set_size() {

}

void read_input(Snake &snake, Field* field) {
    while (1) {
        int ch = _getch();
        if (ch == 27) exit(0);              //escape
        if (ch != 224) continue;            //to assure it's an arrow and not an uppercase key
        ch = _getch();
        unique_lock<mutex> lck(mtx);
        switch(ch) {
        case 75:                            //left arrow
            snake.rotate(direction::LEFT);
            break;
        case 77:                            //right arrow
            snake.rotate(direction::RIGHT);
            break;
        case 72:                            //up arrow
            snake.rotate(direction::UP);
            break;
        case 80:                            //down arrow
            snake.rotate(direction::DOWN);
            break;
        }
    }
}

int main(int argc, char* argv[])
{
    srand(time(NULL));
    set_window();
    Field* field;
    Snake snake;
    set_field(field, snake);

    thread playthread(play, ref(snake), field);
    thread readthread(read_input, ref(snake), field);

    playthread.join();
    readthread.join();
    
    
}
