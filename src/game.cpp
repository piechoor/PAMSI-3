#include "game.hh"


Game::Game() {
    for (int i=0; i<BOARD_SIZE; ++i) {
        for (int j=0; j<BOARD_SIZE; ++j)
            board[i][j] = BLANK_SIGN; //puts blank sign in the whole array 
    }
}

void Game::display_board() {
    if (SYS_CLR) system("clear"); //if specified clears screen before displaying

    for (int i=0; i<BOARD_SIZE; ++i) {
        std::cout << " ";
        for (int j=0; j<BOARD_SIZE; ++j) {
            std::cout << board[i][j];
            if (j!=BOARD_SIZE-1) //prevents puting "|" at the end of the board
                std::cout << " | ";
        }
        std::cout << std::endl;
        if (i!=BOARD_SIZE-1) { //prevents puting "----" at the end
            for (int k=0; k<BOARD_SIZE; ++k)
                std::cout << "----";
        }
        std::cout << std::endl;
    }
}

bool Game::play(int x_board, int y_board, char sign) {
    //throws an error if one wants to access unavailable board's tile
    if (x_board<0 or x_board>=BOARD_SIZE or y_board<0 or y_board>=BOARD_SIZE) {
        std::cerr << "Given index exceeds the board size!\n";
        Sleep(ALERT_TIME);
        return false;
    }
    //throws an error if the tile is taken
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
    //checking descending diagonals, first lower half, then the half above
    for (int i=BOARD_SIZE-3; i>=0; --i) {
        for (int j=0; j<BOARD_SIZE-i; ++j) {
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
        for (int j=0; j<BOARD_SIZE-i; ++j) {
            if (board[i+j][BOARD_SIZE-j-1]==COMP_SIGN) {++player_x; player_o=0;}
            else if (board[i+j][BOARD_SIZE-j-1]==PLAYER_SIGN) {++player_o; player_x=0;}
            if (player_x==WINNING_LENGHT) return 10;
            if (player_o==WINNING_LENGHT) return -10;
            if (board[i+j][BOARD_SIZE-j-1]==BLANK_SIGN) {player_o=0; player_x=0;}
        }
        player_o=0; player_x=0;
    }
    for (int j=1; j<BOARD_SIZE-2; ++j) {
        for (int i=0; i<BOARD_SIZE-j; ++i) {
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
    std::cout << "Type char idx1 idx2 for board[idx1][idx]=char\nType Q to quit\n";
    std::cin >> sign >> x >> y;
    while(sign!='Q') { //put signs till Q is typed
        this->play(x,y,sign);
        this->display_board();
        std::cout << "Type char idx1 idx2 for board[idx1][idx]=char\nType Q to quit\n";
        std::cout << "EVAL:" << this->evaluate() << std::endl; //shows evaluation of the board
        std::cin >> sign >> x >> y;
    }
    this->display_board();
    return;
}

bool Game::is_draw() {
    for (int i=0; i<BOARD_SIZE; ++i) {
        for (int j=0; j<BOARD_SIZE; ++j) {
            if (board[i][j] == BLANK_SIGN) return false; //if there's a blank char, there's no draw
        }
    }
    return true; //if whole board is filled up (without winner), there's a draw
}

int Game::mini_max(int depth, bool is_max_player, int alpha, int beta) {
    if (SHOW_DEPTH) std::cout<<"MiniMax, depth:" << depth << std::endl;
    int best_val, value;
    
    int result = evaluate(); //checking and terminating algorithm if there's victory draw or max depth
    if (result==10 or result==-10)  return result;
    if (is_draw() or depth>=MAX_DEPTH) return 0;

    if (is_max_player) { //maximizing game return value - computer's move
        best_val = -INFINITE_;
        for (int i=0; i<BOARD_SIZE; ++i) {
            for (int j=0; j<BOARD_SIZE; ++j) {
                if (board[i][j] == BLANK_SIGN) {
                    board[i][j] = COMP_SIGN; //computer moves
                    value = mini_max(depth+1, false, alpha, beta);
                    board[i][j] = BLANK_SIGN; //undo
                if (value > best_val) best_val = value;
                if (best_val > alpha) alpha = best_val;
                if (beta <= alpha) break;
                }
            }
        }
        return best_val;
    }

    else { //minimizing game return value - computer's move
        best_val = INFINITE_;
        for (int i=0; i<BOARD_SIZE; ++i) {
            for (int j=0; j<BOARD_SIZE; ++j) {
                if (board[i][j] == BLANK_SIGN) {
                    board[i][j] = PLAYER_SIGN; //player moves
                value = mini_max(depth+1, true, alpha, beta);
                board[i][j] = BLANK_SIGN; //undo
                if (value < best_val) best_val = value;
                if (best_val < beta) beta = best_val;
                if (beta <= alpha) break; //prunes
                }
            }
        }
        return best_val;
    }
}

void Game::computers_move() {
    int best_val=-INFINITE_, value=0, b_move_i=-1, b_move_j=-1;

    std::cout << "Wait for computer's move ... " << std::endl;
    if (BOARD_SIZE<=3) Sleep(ALERT_TIME); //delay if computer moves too fast
    for (int i=0; i<BOARD_SIZE; ++i) {
        for (int j=0; j<BOARD_SIZE; ++j) {
            if (board[i][j] == BLANK_SIGN) {
                board[i][j] = COMP_SIGN; //computer moves
                value = mini_max(0, false, -INFINITE_, +INFINITE_);
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

void Game::players_move() {
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
        this->display_board();

}

bool Game::is_game_finished() {
    if (this->evaluate()==10) { //computer wins
        std::cout << "You have lost!\n";
        Sleep(ALERT_TIME);
        return true;
    }
    else if (this->evaluate()==-10) { //player wins
        std::cout << "You have won!\n";
        Sleep(ALERT_TIME);
        return true;
    }
    else if (is_draw()) { //draw wins
        std::cout << "That is a draw!\n";
        Sleep(ALERT_TIME);
        return true;
    }
    else return false; //no one wins
}