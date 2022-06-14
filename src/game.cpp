#include "game.hh"


Game::Game() {
    for (int i=0; i<BOARD_SIZE; ++i) {
        for (int j=0; j<BOARD_SIZE; ++j)
            board[i][j] = ' ';
    }
    no_moves = 0;
}

void Game::display_board() {
    system("clear");

    this->show_stats();
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
        Sleep(ALERT_TIME);
        return false;
    }
    if (board[x_board][y_board]!=' ') {
        std::cerr << "That square is already taken!";
        Sleep(ALERT_TIME);
        return false;
    }
    this->board[x_board][y_board] = sign;
    no_moves++;

    return true;
}

int Game::evaluate() {
    //checking horizontally
    int player_x=0, player_o=0;
    for (int i=0; i<BOARD_SIZE; ++i) { //rows
        for (int j=0; j<BOARD_SIZE; ++j) { //column
            if (board[i][j]=='x') ++player_x;
            if (board[i][j]=='o') ++player_o;
            if (player_x==WINNING_LENGHT) return 1;
            if (player_o==WINNING_LENGHT) return -1;
            if (board[i][j]==' ') {player_o=0; player_x=0;}
        }
        player_o=0; player_x=0;
    }
    //checking vertically
    player_x=0, player_o=0;
    for (int i=0; i<BOARD_SIZE; ++i) { //columns
        for (int j=0; j<BOARD_SIZE; ++j) { //row
            if (board[j][i]=='x') ++player_x;
            if (board[j][i]=='o') ++player_o;
            if (player_x==WINNING_LENGHT) return 1;
            if (player_o==WINNING_LENGHT) return -1;
            if (board[j][i]==' ') {player_o=0; player_x=0;}
        }
        player_o=0; player_x=0;
    }
    //checking descending diagonals
    
    
}

void Game::fill_manually() {

    char sign; int x,y;
    this->display_board();
    std::cin >> sign >> x >> y;
    while(sign!='Q') {
        this->play(x,y,sign);
        this->display_board();
        std::cout << "EVAL:" << this->evaluate() << std::endl;
        std::cin >> sign >> x >> y;
    }
    return;
}

void Game::show_stats() {
    std::cout << no_moves+1 << ". move\n\n";
}