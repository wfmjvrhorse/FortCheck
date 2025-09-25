#include "Player.h"
#include <iostream>

// Broken constructor implementation
Player::Player(std::string playerName, int hp, int arm) {
    name = playerName;
    health = hp;
    armor = arm;
    posX = 0.0f;
    posY = 0.0f;
    posZ = 0.0f;
    currentWeapon = nullptr;
    
    // Forgot to initialize inventory
}

// Missing destructor implementation causes linker error

// Wrong return type implementations
void Player::getName() const {
    return name;  // Trying to return string from void function
}

int Player::setHealth(int newHealth) {
    health = newHealth;
    // Missing return statement
}

bool Player::getHealth() const {
    return health;  // Returning int as bool
}

// Wrong parameter count
void Player::move(float x, float y) {
    posX += x;
    posY += y;
    // Missing posZ parameter but trying to update it
    posZ += z;
}

void Player::attack(Player target) {
    if (currentWeapon == nullptr) {
        std::cout << name << " has no weapon!" << std::endl;
        return;
    }
    
    // Trying to modify copy instead of original
    int damage = currentWeapon->getDamage();
    target.health -= damage;  // Should be target.setHealth()
    
    // Undefined method call
    currentWeapon->use();
}

// Missing const qualifier implementations
float Player::getPositionX() {
    return posX;
}

float Player::getPositionY() {
    return posY;
}


// Unimplemented methods - will cause linker errors

