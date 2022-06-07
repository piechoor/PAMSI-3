#pragma once

#include <iostream>
#include <stdlib.h>
#include "settings.hh"

class Game {

    char board[BOARD_SIZE][BOARD_SIZE];

    public:

        Game();
        void display_board();
        bool play(int x_board, int y_board, char sign);
        void fill_manually();

};