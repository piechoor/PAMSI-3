#include "game.hh"

int main() {
    
    Game g;
    while(true) {
        g.player_move();
        if(g.is_game_finished()) break;
        g.computer_move();
        if(g.is_game_finished()) break;
    }
    return 0;
}