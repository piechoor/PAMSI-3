#include "game.hh"

Game::Game() {
    for (int i=0; i<BOARD_SIZE; ++i) {
        for (int j=0; j<BOARD_SIZE; ++j)
            board[i][j] = ' ';
    }
}

void Game::display_board() {
    system("clear");

    for (int i=0; i<BOARD_SIZE; ++i) {
        std::cout << " ";
        for (int j=0; j<BOARD_SIZE; ++j) {
            std::cout << board[i][j];
            if (j!=BOARD_SIZE-1)
                std::cout << " | ";
        }
        std::cout << std::endl;
        if (i!=BOARD_SIZE-1) {
            for (int k=0; k<BOARD_SIZE; ++k)
                std::cout << "----";
        }
        std::cout << std::endl;
    }
}

bool Game::play(int x_board, int y_board, char sign) {
    if (x_board<0 or x_board>=BOARD_SIZE or y_board<0 or y_board>=BOARD_SIZE) {
        std::cerr << "Given index exceeds the board size!";
        return false;
    }
    if (board[x_board][y_board]!=' ') {
        std::cerr << "That square is already taken!";
        return false;
    }
    this->board[x_board][y_board] = sign;
    return true;
}

void Game::fill_manually() {

    char sign; int x,y;
    this->display_board();
    std::cin >> sign >> x >> y;
    while(sign!='Q') {
        this->play(x,y,sign);
        this->display_board();
        std::cin >> sign >> x >> y;
    }
    return;
}