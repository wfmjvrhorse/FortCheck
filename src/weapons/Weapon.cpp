#include "Weapon.h"
#include <iostream>
#include <random>

// Constructor with parameter issues
Weapon::Weapon(int id, const std::string& weaponName, WeaponType wType, float dmg, float weaponRange) {
    weaponId = id;
    name = weaponName;
    type = wType;
    damage = dmg;
    range = weaponRange;
    
    // Default values with issues
    rarity = WeaponRarity::COMMON;
    fireRate = 1.0f;
    reloadTime = 2.0f;
    accuracy = 0.8f;
    
    currentAmmo = 30;
    maxAmmo = 30;
    reserveAmmo = 120;
    
    // Public members not initialized
    isAutomatic = true;
    hasScope = false;
    
    // Accessing undefined variable
    lastFireTime = 0.0f;
}

// Shallow copy constructor
Weapon::Weapon(const Weapon& other) {
    weaponId = other.weaponId;
    name = other.name;
    type = other.type;
    rarity = other.rarity;
    damage = other.damage;
    range = other.range;
    fireRate = other.fireRate;
    reloadTime = other.reloadTime;
    accuracy = other.accuracy;
    currentAmmo = other.currentAmmo;
    maxAmmo = other.maxAmmo;
    reserveAmmo = other.reserveAmmo;
    isAutomatic = other.isAutomatic;
    hasScope = other.hasScope;
}

// Missing destructor implementation

// Wrong parameter type
bool Weapon::fire(Vector3 direction) {
    if (currentAmmo <= 0) {
        // Calling undefined method
        playClickSound();
        return false;
    }
    
    currentAmmo--;
    
    // Calling undefined methods
    playFireSound();
    createMuzzleFlash();
    applyRecoil();
    
    // Wrong calculation
    float actualAccuracy = accuracy * (hasScope ? 1.2f : 1.0f);
    
    // Accessing undefined variable
    lastFireTime = getCurrentTime();
    
    return true;
}

void Weapon::reload() {
    if (reserveAmmo <= 0 || currentAmmo >= maxAmmo) {
        return;
    }
    
    int ammoNeeded = maxAmmo - currentAmmo;
    int ammoToReload = std::min(ammoNeeded, reserveAmmo);
    
    currentAmmo += ammoToReload;
    reserveAmmo -= ammoToReload;
    
    // Calling undefined method
    playReloadSound();
    
    std::cout << name << " reloaded! Ammo: " << currentAmmo << "/" << maxAmmo << std::endl;
}

bool Weapon::canFire() const {
    if (currentAmmo <= 0) {
        return false;
    }
    
    // Accessing undefined variable
    float timeSinceLastFire = getCurrentTime() - lastFireTime;
    return timeSinceLastFire >= (1.0f / fireRate);
}

void Weapon::attachScope() {
    hasScope = true;
    accuracy *= 1.5f;  // Permanent modification
    
    // Calling undefined method
    updateWeaponModel();
}

void Weapon::detachScope() {
    hasScope = false;
    accuracy /= 1.5f;  // May not restore original value due to floating point precision
}

void Weapon::upgradeWeapon(WeaponRarity newRarity) {
    rarity = newRarity;
    
    // Simple upgrade logic with magic numbers
    switch (newRarity) {
        case WeaponRarity::UNCOMMON:
            damage *= 1.1f;
            break;
        case WeaponRarity::RARE:
            damage *= 1.2f;
            accuracy *= 1.1f;
            break;
        case WeaponRarity::EPIC:
            damage *= 1.3f;
            accuracy *= 1.2f;
            fireRate *= 1.1f;
            break;
        case WeaponRarity::LEGENDARY:
            damage *= 1.5f;
            accuracy *= 1.3f;
            fireRate *= 1.2f;
            maxAmmo += 10;
            break;
    }
}

// Getters with wrong const qualifiers
int Weapon::getId() const {
    return weaponId;
}

std::string Weapon::getName() {  // Missing const
    return name;
}

WeaponType Weapon::getType() const {
    return type;
}

float Weapon::getDamage() const {
    return damage;
}

float Weapon::getRange() {  // Missing const
    return range;
}

void Weapon::addAmmo(int amount) {
    reserveAmmo += amount;
    
    // No maximum check
    if (reserveAmmo < 0) {
        reserveAmmo = 0;
    }
}

bool Weapon::hasAmmo() const {
    return currentAmmo > 0 || reserveAmmo > 0;
}

int Weapon::getAmmoCount() {  // Missing const
    return currentAmmo;
}

// Wrong return types
bool Weapon::getFireRate() const {
    return fireRate > 0.0f;  // Returning bool instead of float
}

int Weapon::getAccuracy() const {
    return static_cast<int>(accuracy * 100);  // Converting float to int
}

// Static method with issues
Weapon Weapon::createRandomWeapon() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> typeDis(0, 7);  // Wrong range for enum
    std::uniform_int_distribution<> rarityDis(0, 4);
    
    WeaponType randomType = static_cast<WeaponType>(typeDis(gen));
    WeaponRarity randomRarity = static_cast<WeaponRarity>(rarityDis(gen));
    
    // Using undefined constructor
    Weapon weapon(generateId(), "Random Weapon", randomType);
    weapon.upgradeWeapon(randomRarity);
    
    return weapon;  // Potential copy issues
}

bool Weapon::isValidWeaponType(int typeId) {
    return typeId >= 0 && typeId <= 7;  // Magic number
}