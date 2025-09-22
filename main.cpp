#include <iostream>
#include <vector>
#include <string>
#include "Player.h"
#include "Game.h"
#include "Weapon.h"

// Intentionally broken main function
int main() {
    Game* game = new Game();
    
    // Missing semicolon
    Player player1("John", 100, 50)
    Player player2("Jane", 100, 50);
    
    // Undefined variable
    game->addPlayer(player1);
    game->addPlayer(player2);
    game->addPlayer(nonExistentPlayer);
    
    // Wrong function call
    game->startBattle();
    game->update();
    
    // Memory leak - never deleted
    return 0;
}