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
    for (int i=BOARD_SIZE-2; i>=0; --i) {
        for (int j=0; j<BOARD_SIZE-i; ++j) {
            if(i+j>=BOARD_SIZE or i+j<0 or j>=BOARD_SIZE or j<0) return-5;
            if (board[i+j][j]=='x') ++player_x;
            if (board[i+j][j]=='o') ++player_o;
            if (player_x==WINNING_LENGHT) return 1;
            if (player_o==WINNING_LENGHT) return -1;
            if (board[i+j][j]==' ') {player_o=0; player_x=0;}
        }
        player_o=0; player_x=0;
    }
    for (int j=1; j<BOARD_SIZE-1; ++j) {
        for (int i=0; i<BOARD_SIZE-j; ++i) {
            //if(i+j>=BOARD_SIZE or i+j<0 or i>=BOARD_SIZE or i<0) return-5;
            //board[i][i+j]='C';

            if (board[i][i+j]=='x') ++player_x;
            if (board[i][i+j]=='o') ++player_o;
            if (player_x==WINNING_LENGHT) return 1;
            if (player_o==WINNING_LENGHT) return -1;
            if (board[i][i+j]==' ') {player_o=0; player_x=0;}
        }
        player_o=0; player_x=0;
    }
    //checking ascending diagonals //BY TRANSFORMING BOARD POSITION (i,j)->(i,-j)->(i,-j+BOARD_SIZE-1)
                                   //that makes diagonals descending and previous algorithm works
    for (int i=BOARD_SIZE-2; i>=0; --i) {
        for (int j=0; j<BOARD_SIZE-i; ++j) { //going through a certain diagonal
            //board[i+j][BOARD_SIZE-j-1]='C';
            //if(i+j>=BOARD_SIZE or i+j<0 or (BOARD_SIZE-j-1)>=BOARD_SIZE or (BOARD_SIZE-j-1)<0) return-5;
            if (board[i+j][BOARD_SIZE-j-1]=='x') ++player_x;
            if (board[i+j][BOARD_SIZE-j-1]=='o') ++player_o;
            if (player_x==WINNING_LENGHT) return 1;
            if (player_o==WINNING_LENGHT) return -1;
            if (board[i+j][BOARD_SIZE-j-1]==' ') {player_o=0; player_x=0;}
        }
        player_o=0; player_x=0;
    }
    for (int j=1; j<BOARD_SIZE-1; ++j) {
        for (int i=0; i<BOARD_SIZE-j; ++i) { //going through a certain diagonal
            //if((BOARD_SIZE-i-j-1)>=BOARD_SIZE or (BOARD_SIZE-i-j-1)<0 or i>=BOARD_SIZE or i<0) return-5;
            //board[i][BOARD_SIZE-i-j-1]='C';
            if (board[i][BOARD_SIZE-i-j-1]=='x') ++player_x;
            if (board[i][BOARD_SIZE-i-j-1]=='o') ++player_o;
            if (player_x==WINNING_LENGHT) return 1;
            if (player_o==WINNING_LENGHT) return -1;
            if (board[i][BOARD_SIZE-i-j-1]==' ') {player_o=0; player_x=0;}
        }
        player_o=0; player_x=0;
    }
    return 0;
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