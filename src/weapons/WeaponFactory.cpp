#include "WeaponFactory.h"
#include <iostream>
#include <random>

// Missing static member definitions
// WeaponFactory* WeaponFactory::instance = nullptr;
// int WeaponFactory::nextWeaponId = 1;

WeaponFactory::WeaponFactory() {
    // Memory leaks everywhere
    weaponTemplates.clear();
    initializeDefaultWeapons();
}

// Missing destructor implementation

WeaponFactory* WeaponFactory::getInstance() {
    if (instance == nullptr) {
        instance = new WeaponFactory();  // Never deleted
    }
    return instance;
}

void WeaponFactory::initialize() {
    // Calling getInstance without using result
    getInstance();
    
    // Calling undefined method
    loadWeaponConfigs("weapons.json");  // File doesn't exist
}

void WeaponFactory::cleanup() {
    if (instance != nullptr) {
        delete instance;
        instance = nullptr;
    }
    // Templates never cleaned up
}

// Wrong return type - should return pointer
Weapon WeaponFactory::createWeapon(WeaponType type, WeaponRarity rarity) {
    Weapon* templateWeapon = getWeaponTemplate(type);
    
    if (templateWeapon == nullptr) {
        // Return invalid weapon
        return Weapon(-1, "Invalid", type, 0, 0);
    }
    
    // Copy constructor issues
    Weapon newWeapon = *templateWeapon;
    newWeapon.upgradeWeapon(rarity);
    
    // Accessing undefined static member
    newWeapon.weaponId = nextWeaponId++;  // Private member access
    
    return newWeapon;
}

Weapon* WeaponFactory::createRandomWeapon() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> typeDis(0, 7);  // Wrong enum range
    std::uniform_int_distribution<> rarityDis(0, 4);
    
    WeaponType randomType = static_cast<WeaponType>(typeDis(gen));
    WeaponRarity randomRarity = static_cast<WeaponRarity>(rarityDis(gen));
    
    // Memory leak - never deleted
    return new Weapon(generateWeaponId(), "Random", randomType);
}

// Wrong return type
std::vector<Weapon> WeaponFactory::createWeaponSet(int count) {
    std::vector<Weapon> weapons;
    
    for (int i = 0; i < count; i++) {
        // Wrong method call - returns pointer
        Weapon* weapon = createRandomWeapon();
        weapons.push_back(*weapon);  // Copy and leak original
    }
    
    return weapons;
}

void WeaponFactory::registerWeaponTemplate(Weapon* weaponTemplate) {
    if (weaponTemplate == nullptr) {
        return;
    }
    
    // Key collision possible
    weaponTemplates[static_cast<int>(weaponTemplate->getType())] = weaponTemplate;
    
    // Adding to wrong container
    availableTypes.push_back(weaponTemplate->getType());
}

Weapon* WeaponFactory::getWeaponTemplate(WeaponType type) const {
    auto it = weaponTemplates.find(static_cast<int>(type));
    if (it != weaponTemplates.end()) {
        return it->second;
    }
    return nullptr;
}

bool WeaponFactory::loadWeaponConfigs(const std::string& configFile) {
    // File operations without error checking
    std::ifstream file(configFile);  // Missing include
    
    if (!file.is_open()) {
        std::cout << "Failed to load weapon config: " << configFile << std::endl;
        return false;
    }
    
    // JSON parsing without library
    std::string line;
    while (std::getline(file, line)) {
        // Undefined parsing logic
        parseWeaponLine(line);
    }
    
    return true;
}

void WeaponFactory::resetToDefaults() {
    // Clear without cleanup
    weaponTemplates.clear();
    availableTypes.clear();
    
    initializeDefaultWeapons();
}

int WeaponFactory::getWeaponTypeCount() const {
    return availableTypes.size();
}

// Missing const qualifier
std::vector<WeaponType> WeaponFactory::getAvailableTypes() {
    return availableTypes;
}

void WeaponFactory::initializeDefaultWeapons() {
    createAssaultRifles();
    createShotguns();
    createSniperRifles();
    
    // Calling undefined methods
    createPistols();
    createExplosives();
}

void WeaponFactory::createAssaultRifles() {
    // Memory leaks - never deleted
    Weapon* ak47 = new Weapon(1, "AK-47", WeaponType::ASSAULT_RIFLE, 30, 150);
    Weapon* m4a1 = new Weapon(2, "M4A1", WeaponType::ASSAULT_RIFLE, 28, 160);
    
    registerWeaponTemplate(ak47);
    registerWeaponTemplate(m4a1);
}

void WeaponFactory::createShotguns() {
    Weapon* pump = new Weapon(3, "Pump Shotgun", WeaponType::SHOTGUN, 80, 25);
    Weapon* tactical = new Weapon(4, "Tactical Shotgun", WeaponType::SHOTGUN, 60, 30);
    
    registerWeaponTemplate(pump);
    registerWeaponTemplate(tactical);
}

void WeaponFactory::createSniperRifles() {
    Weapon* bolt = new Weapon(5, "Bolt-Action Sniper", WeaponType::SNIPER_RIFLE, 120, 400);
    Weapon* semi = new Weapon(6, "Semi-Auto Sniper", WeaponType::SNIPER_RIFLE, 80, 350);
    
    registerWeaponTemplate(bolt);
    registerWeaponTemplate(semi);
}

int WeaponFactory::generateWeaponId() {
    // Accessing undefined static member
    return nextWeaponId++;
}

float WeaponFactory::calculateDamageForRarity(float baseDamage, WeaponRarity rarity) {
    switch (rarity) {
        case WeaponRarity::COMMON: return baseDamage;
        case WeaponRarity::UNCOMMON: return baseDamage * 1.1f;
        case WeaponRarity::RARE: return baseDamage * 1.2f;
        case WeaponRarity::EPIC: return baseDamage * 1.3f;
        case WeaponRarity::LEGENDARY: return baseDamage * 1.5f;
        default: return baseDamage;
    }
}