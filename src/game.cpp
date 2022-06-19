#include "game.hh"


Game::Game() {
    for (int i=0; i<BOARD_SIZE; ++i) {
        for (int j=0; j<BOARD_SIZE; ++j)
            board[i][j] = BLANK_SIGN;
    }
    // board[0][0] = PLAYER_SIGN;
    // board[0][1] = COMP_SIGN;
    // board[0][2] = PLAYER_SIGN;
    // board[1][0] = BLANK_SIGN;
    // board[1][1] = COMP_SIGN;
    // board[1][2] = BLANK_SIGN;
    // board[2][0] = BLANK_SIGN;
    // board[2][1] = BLANK_SIGN;
    // board[2][2] = BLANK_SIGN;
    // board[3][0] = BLANK_SIGN;
    // board[3][1] = BLANK_SIGN;
    // board[3][2] = BLANK_SIGN;
}

void Game::display_board() {
    if (SYS_CLR) system("clear");

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
    //std::cout << "EVAL:" << this->evaluate() << std::endl;
}

bool Game::play(int x_board, int y_board, char sign) {
    if (x_board<0 or x_board>=BOARD_SIZE or y_board<0 or y_board>=BOARD_SIZE) {
        std::cerr << "Given index exceeds the board size!\n";
        Sleep(ALERT_TIME);
        return false;
    }
    if (board[x_board][y_board]!=BLANK_SIGN) {
        std::cerr << "That square is already taken!\n";
        Sleep(ALERT_TIME);
        return false;
    }
    this->board[x_board][y_board] = sign;

    return true;
}

int Game::evaluate() {
    //checking horizontally
    int player_x=0, player_o=0;
    for (int i=0; i<BOARD_SIZE; ++i) { //rows
        for (int j=0; j<BOARD_SIZE; ++j) { //column
            if (board[i][j]==COMP_SIGN) {++player_x; player_o=0;}
            else if (board[i][j]==PLAYER_SIGN) {++player_o; player_x=0;}
            if (player_x==WINNING_LENGHT) return 10;
            if (player_o==WINNING_LENGHT) return -10;
            if (board[i][j]==BLANK_SIGN) {player_o=0; player_x=0;}
        }
        player_o=0; player_x=0;
    }
    //checking vertically
    player_x=0, player_o=0;
    for (int i=0; i<BOARD_SIZE; ++i) { //columns
        for (int j=0; j<BOARD_SIZE; ++j) { //row
            if (board[j][i]==COMP_SIGN) {++player_x; player_o=0;}
            else if (board[j][i]==PLAYER_SIGN) {++player_o; player_x=0;}
            if (player_x==WINNING_LENGHT) return 10;
            if (player_o==WINNING_LENGHT) return -10;
            if (board[j][i]==BLANK_SIGN) {player_o=0; player_x=0;}
        }
        player_o=0; player_x=0;
    }
    //checking descending diagonals
    for (int i=BOARD_SIZE-3; i>=0; --i) {
        for (int j=0; j<BOARD_SIZE-i; ++j) {
            //if(i+j>=BOARD_SIZE or i+j<0 or j>=BOARD_SIZE or j<0) return-5;
            if (board[i+j][j]==COMP_SIGN) {++player_x; player_o=0;}
            else if (board[i+j][j]==PLAYER_SIGN) {++player_o; player_x=0;}
            if (player_x==WINNING_LENGHT) return 10;
            if (player_o==WINNING_LENGHT) return -10;
            if (board[i+j][j]==BLANK_SIGN) {player_o=0; player_x=0;}
        }
        player_o=0; player_x=0;
    }
    for (int j=1; j<BOARD_SIZE-2; ++j) {
        for (int i=0; i<BOARD_SIZE-j; ++i) {
            //if(i+j>=BOARD_SIZE or i+j<0 or i>=BOARD_SIZE or i<0) return-5;
            //board[i][i+j]='C';

            if (board[i][i+j]==COMP_SIGN) {++player_x; player_o=0;}
            else if (board[i][i+j]==PLAYER_SIGN) {++player_o; player_x=0;}
            if (player_x==WINNING_LENGHT) return 10;
            if (player_o==WINNING_LENGHT) return -10;
            if (board[i][i+j]==BLANK_SIGN) {player_o=0; player_x=0;}
        }
        player_o=0; player_x=0;
    }
    //checking ascending diagonals //BY TRANSFORMING BOARD POSITION (i,j)->(i,-j)->(i,-j+BOARD_SIZE-1)
                                   //that makes diagonals descending and previous algorithm works
    for (int i=BOARD_SIZE-3; i>=0; --i) {
        for (int j=0; j<BOARD_SIZE-i; ++j) { //going through a certain diagonal
            //board[i+j][BOARD_SIZE-j-1]='C';
            //if(i+j>=BOARD_SIZE or i+j<0 or (BOARD_SIZE-j-1)>=BOARD_SIZE or (BOARD_SIZE-j-1)<0) return-5;
            if (board[i+j][BOARD_SIZE-j-1]==COMP_SIGN) {++player_x; player_o=0;}
            else if (board[i+j][BOARD_SIZE-j-1]==PLAYER_SIGN) {++player_o; player_x=0;}
            if (player_x==WINNING_LENGHT) return 10;
            if (player_o==WINNING_LENGHT) return -10;
            if (board[i+j][BOARD_SIZE-j-1]==BLANK_SIGN) {player_o=0; player_x=0;}
        }
        player_o=0; player_x=0;
    }
    for (int j=1; j<BOARD_SIZE-2; ++j) {
        for (int i=0; i<BOARD_SIZE-j; ++i) { //going through a certain diagonal
            //if((BOARD_SIZE-i-j-1)>=BOARD_SIZE or (BOARD_SIZE-i-j-1)<0 or i>=BOARD_SIZE or i<0) return-5;
            //board[i][BOARD_SIZE-i-j-1]='C';
            if (board[i][BOARD_SIZE-i-j-1]==COMP_SIGN) {++player_x; player_o=0;}
            else if (board[i][BOARD_SIZE-i-j-1]==PLAYER_SIGN) {++player_o; player_x=0;}
            if (player_x==WINNING_LENGHT) return 10;
            if (player_o==WINNING_LENGHT) return -10;
            if (board[i][BOARD_SIZE-i-j-1]==BLANK_SIGN) {player_o=0; player_x=0;}
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

bool Game::is_draw() {
    for (int i=0; i<BOARD_SIZE; ++i) {
        for (int j=0; j<BOARD_SIZE; ++j) {
            if (board[i][j] == BLANK_SIGN) return false;
        }
    }
    return true;
}

int Game::mini_max(int depth, bool is_max_player) {
    int best_val, value;
    
    int result = evaluate();
    if (result==10 or result==-10)
        return result;
    if (result==-5) exit(0);
    //std::cout<<"MiniMax, depth:" << depth << std::endl;;
    if (is_draw() or depth>=MAX_DEPTH) return 0; // or depth>=MAX_DEPTH

    if (is_max_player) {
        best_val = -INFINITE_;
        for (int i=0; i<BOARD_SIZE; ++i) {
            for (int j=0; j<BOARD_SIZE; ++j) {
                if (board[i][j] == BLANK_SIGN) {
                    board[i][j] = COMP_SIGN; //computer moves
                    value = mini_max(depth+1, false);
                    board[i][j] = BLANK_SIGN; //undo
                if (value > best_val) best_val = value;
                }
            }
        }
        return best_val;
    }

    else {
        best_val = INFINITE_;
        for (int i=0; i<BOARD_SIZE; ++i) {
            for (int j=0; j<BOARD_SIZE; ++j) {
                if (board[i][j] == BLANK_SIGN) {
                    board[i][j] = PLAYER_SIGN; //player moves
                value = mini_max(depth+1, true);
                board[i][j] = BLANK_SIGN; //undo
                if (value < best_val) best_val = value;
                }
            }
        }
        return best_val;
    }
}

void Game::computer_move() {
    int best_val=-INFINITE_, value=0, b_move_i=-1, b_move_j=-1;

    std::cout << "Wait for computer's move ... " << std::endl;
    if (BOARD_SIZE<=3) Sleep(ALERT_TIME);
    for (int i=0; i<BOARD_SIZE; ++i) {
        for (int j=0; j<BOARD_SIZE; ++j) {
            if (board[i][j] == BLANK_SIGN) {
                board[i][j] = COMP_SIGN; //computer moves
                value = mini_max(0, false);
                board[i][j] = BLANK_SIGN; //undo
                if (value > best_val) {
                    best_val = value;
                    b_move_i = i;
                    b_move_j = j;
                }
            }
        }
    }

    this->board[b_move_i][b_move_j] = COMP_SIGN;
    this->display_board();
}

void Game::player_move() {
        system("clear");
        std::cout << "Your turn:\n";
        int x,y;
        this->display_board();
        std::cin >> x >> y;
        while(!this->play(x,y,PLAYER_SIGN)) {
            std::cout << "Try one more time:\n";
            this->display_board();
            std::cin >> x >> y;
        }

}

bool Game::is_game_finished() {
    if (this->evaluate()==10) {
        std::cout << "You have lost!\n";
        Sleep(ALERT_TIME);
        return true;
    }
    else if (this->evaluate()==-10) {
        std::cout << "You have won!\n";
        Sleep(ALERT_TIME);
        return true;
    }
    else if (is_draw()) {
        std::cout << "That is a draw!\n";
        Sleep(ALERT_TIME);
        return true;
    }
    else return false;
}