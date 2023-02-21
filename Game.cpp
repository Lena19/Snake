// Snake.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <chrono>
#include <conio.h>
#include <ctime>
#include <iostream>
#include <mutex>
#include <random>
#include <thread>
#include <vector>
#include <Windows.h>
#include "Console_field.h"
#include "Console_status_field.h"
#include "Snake.h"

using namespace std;

int WIDTH = 20;
int HEIGHT = 20;
int initial_sleep_timer = 300, sleep_timer = 300;

mutex mtx;

void set_window() {
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r);
    MoveWindow(console, r.left, r.top, WIDTH * 25, HEIGHT * 30, true);
}

void set_field(Field*& f, Snake & s, Status_field*& csf) {

    f = new Console_field(HEIGHT + 1, WIDTH + 1);
    csf = new Console_status_field(5, WIDTH + 1);
    csf->update_info("Score", 0);
    csf->update_info("Speed", 1);
  
    int head_posx = rand() % (WIDTH / 2) + 1;
    int head_posy = rand() % (HEIGHT / 2) + 1;
    Cell* head_cell = new Console_cell;
    s = Snake(head_posx, head_posy, f, head_cell);

    while (!f->spawn_target());
    sleep_timer = initial_sleep_timer;
}

void play(Snake &snake, Field* field, Status_field* csfield) {
    auto start_time = chrono::high_resolution_clock::now();
    int score = 0, speed = 1;
    while (1) {
        field->draw(); 
        csfield->draw();
        //unique_lock<mutex> lck(mtx);
        int status = snake.move();
        if (status == -1) {
            set_field(field, snake, csfield);
            start_time = chrono::high_resolution_clock::now();
            score = 0, speed = 1; 
            status = 0;
        }
        score += status;
        csfield->update_info("Score", score);
        if (status != 0 and score and score % 5 == 0) {
            speed++;
            csfield->update_info("Speed", speed);
            sleep_timer = max(sleep_timer - 20, 20);
        }
        //lck.unlock();
        /*
        auto cur_time = chrono::high_resolution_clock::now();
        if (chrono::duration_cast<chrono::seconds>(cur_time - start_time) >= chrono::seconds(10)) {
            start_time = cur_time;
            sleep_timer = max(sleep_timer - 20, 20);
            speed++;
            csfield->update_info("Speed", speed);
        }
        */
        Sleep(sleep_timer);
        system("cls");
    }
}

void set_size(int argc, char* argv[]) {
    //format of AxB or AXB, wherre A and B are integer numbers >= 20
    if (argc > 1) {
        int h = 0, w = 0;
        int xpos = -1;                          //index of x or X in argv[1]
        for (int i = 0; argv[1][i] != '\0'; i++) {
            if (isdigit(argv[1][i])) {
                h *= 10; 
                h += argv[1][i] - '0';
            }
            else if (argv[1][i] == 'x' or argv[1][i] == 'X') {
                xpos = i;
                break;
            }
            else {
                return;
            }
        }
        if (xpos == -1) return;                 //x or X was not found
        for (int i = xpos + 1; argv[1][i] != '\0'; i++) {
            if (isdigit(argv[1][i])) {
                w *= 10;
                w += argv[1][i] - '0';
            }
            else {
                return;
            }
        }
        HEIGHT = min(h, 40);
        WIDTH = min(w, 40);
    }
}

void read_input(Snake &snake) {
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
    
    set_size(argc, argv);
    set_window();
    Field* field;
    Status_field* csfield;
    Snake snake;
    set_field(field, snake, csfield);

    thread playthread(play, ref(snake), field, csfield);
    thread readthread(read_input, ref(snake));

    playthread.join();
    readthread.join();
    
    
}
