#pragma once

#include <iostream>
#include <Windows.h>
#include "settings.hh"

class Game {

    char board[BOARD_SIZE][BOARD_SIZE];

    int evaluate();
    bool play(int x_board, int y_board, char sign);
    int mini_max(int depth, bool is_max_player, int alpha, int beta);
    bool is_draw();
    void display_board();
    
    public:

        Game();
        void fill_manually();
        void computer_move();
        void player_move();
        bool is_game_finished();

};