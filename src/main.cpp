#include "game.hh"

int main() {
    
    Game g;

    if (COMP_FIRST) g.computer_move();
    while(true) {
        g.player_move();
        if(g.is_game_finished()) break;
        g.computer_move();
        if(g.is_game_finished()) break;
    }
    
    return 0;
}