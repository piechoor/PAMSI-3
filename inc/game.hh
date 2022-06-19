#pragma once

#include <iostream>
#include <Windows.h> //function needed to clear the terminal window and sleep() function

#include "settings.hh"

class Game {

    char board[BOARD_SIZE][BOARD_SIZE]; //2D array with elements representing board's tiles

    int evaluate(); //function returns value depending on which player won or 0 if none of them won
    bool play(int x_board, int y_board, char sign); //puts 'sign' into board[x_board][y_board]
    int mini_max(int depth, bool is_max_player, int alpha, int beta); //minimax algorithm with alpha-beta prunings
    bool is_draw(); //returns true if board is in a tie position
    void display_board(); //displayes formated board in the terminal
    
    public:

        Game(); //constructor filling board with blank characters
        void fill_manually(); //helping function for debugging
        void computers_move(); //lets computer make a move
        void players_move(); //lets player make a move
        bool is_game_finished(); //checks if game has ended with draw or victory from one side

};