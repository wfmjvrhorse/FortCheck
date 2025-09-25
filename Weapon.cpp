#include "Weapon.h"
#include <iostream>
#include <random>

// Constructor implementation with parameter mismatch
Weapon::Weapon(std::string weaponName, int dmg, int ammunition, WeaponType wType, float weaponRange) {
    name = weaponName;
    damage = dmg;
    ammo = ammunition;
    maxAmmo = ammunition;
    type = wType;
    range = weaponRange;
    
    // Accessing undefined member
    fireRate = 1.0f;
}

// Copy constructor with shallow copy problem
Weapon::Weapon(const Weapon& other) {
    name = other.name;
    damage = other.damage;
    ammo = other.ammo;
    maxAmmo = other.maxAmmo;
    type = other.type;
    range = other.range;
    // Missing proper deep copy if needed
}

int Weapon::getDamage() const {
    return damage;
}

// Missing const qualifier
int Weapon::getAmmo() {
    return ammo;
}

void Weapon::setAmmo(int newAmmo) {
    if (newAmmo < 0) {
        ammo = 0;
    } else if (newAmmo > maxAmmo) {
        ammo = maxAmmo;
    } else {
        ammo = newAmmo;
    }
}

bool Weapon::fire() {
    if (ammo > 0) {
        ammo--;
        std::cout << "Fired " << name << "! Ammo left: " << ammo << std::endl;
        return true;
    } else {
        std::cout << "Click! " << name << " is out of ammo!" << std::endl;
        return false;
    }
}

void Weapon::reload() {
    ammo = maxAmmo;
    std::cout << name << " reloaded!" << std::endl;
}

// Static method with wrong implementation
Weapon Weapon::createRandomWeapon() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 4);
    
    WeaponType randomType = static_cast<WeaponType>(dis(gen));
    
    // Using undefined constructor
    switch (randomType) {
        case ASSAULT_RIFLE:
            return Weapon("AK-47", 30, 30, ASSAULT_RIFLE);  // Missing last parameter
        case SHOTGUN:
            return Weapon("Pump Shotgun", 80, 8, SHOTGUN, 25.0f);
        case SNIPER_RIFLE:
            return Weapon("Sniper", 120, 5, SNIPER_RIFLE, 300.0f);
        case PISTOL:
            return Weapon("Pistol", 25, 12, PISTOL, 50.0f);
        case SMG:
            return Weapon("SMG", 20, 40, SMG, 75.0f);
        default:
            // Undefined enum value
            return Weapon("Unknown", 0, 0, GRENADE_LAUNCHER, 0.0f);
    }
}

// Missing const qualifiers
std::string Weapon::getName() {
    return name;
}

WeaponType Weapon::getType() {
    return type;
}
dfdbn

// Missing implementation for use() method referenced in Player.cpp
