#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <memory>
#include "../weapons/Weapon.h"
#include "../utils/Vector3.h"
#include "../inventory/Inventory.h"

class Player {
private:
    int playerId;
    std::string playerName;
    float health;
    float maxHealth;
    float shield;
    float maxShield;
    
    Vector3 position;
    Vector3 velocity;
    Vector3 rotation;
    
    Inventory* inventory;
    Weapon* currentWeapon;
    
    // Missing proper encapsulation
public:
    int kills;
    int deaths;
    bool isAlive;
    
    // Constructor with parameter mismatch
    Player(int id, const std::string& name, float hp = 100.0f);
    
    // Copy constructor with shallow copy issues
    Player(const Player& other);
    
    // Missing assignment operator
    
    // Virtual destructor missing
    ~Player();
    
    // Methods with wrong signatures
    void takeDamage(float damage, Player* attacker);
    bool heal(float amount);
    void addShield(float amount);
    
    // Movement methods with wrong parameters
    void move(Vector3 direction, float speed);
    void jump();
    void crouch(bool state);
    
    // Combat methods
    bool attack(Player& target);  // Should be pointer
    void reload();
    bool pickupWeapon(Weapon weapon);  // Wrong parameter type
    
    // Getters with inconsistent const
    int getId() const;
    std::string getName();  // Missing const
    float getHealth() const;
    Vector3 getPosition();  // Missing const
    
    // Setters with wrong types
    void setPosition(float x, float y, float z);
    bool setHealth(float newHealth);  // Wrong return type
    
    // Undefined methods referenced elsewhere
    void updateMovement(float deltaTime);
    void updateAnimations();
    bool isInRange(const Player& other, float range) const;
};

#endif