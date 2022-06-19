#include "game.hh"

int main() {
    
    Game g;

    if (DEBUGGING) g.fill_manually();
    if (COMP_FIRST) g.computers_move();
    while(true) {
        g.players_move();
        if(g.is_game_finished()) break;
        g.computers_move();
        if(g.is_game_finished()) break;
    }
    
    return 0;
}