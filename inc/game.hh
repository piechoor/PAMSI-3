#pragma once

#include <iostream>
#include <Windows.h>
#include "settings.hh"
#include "graph_list.hh"

class Game {

    char board[BOARD_SIZE][BOARD_SIZE];
    int no_moves;

    void show_stats();
    
    public:

        Game();
        void display_board();
        bool play(int x_board, int y_board, char sign);
        void fill_manually();
        int evaluate();

};