#ifndef WEAPONFACTORY_H
#define WEAPONFACTORY_H

#include <map>
#include <vector>
#include <memory>
#include "Weapon.h"

class WeaponFactory {
private:
    static WeaponFactory* instance;
    std::map<int, Weapon*> weaponTemplates;
    std::vector<WeaponType> availableTypes;
    
    // Private constructor for singleton
    WeaponFactory();
    
public:
    // Singleton access
    static WeaponFactory* getInstance();
    static void initialize();
    static void cleanup();
    
    // Factory methods with wrong signatures
    Weapon createWeapon(WeaponType type, WeaponRarity rarity);  // Should return pointer
    Weapon* createRandomWeapon();
    std::vector<Weapon> createWeaponSet(int count);  // Wrong return type
    
    // Template management
    void registerWeaponTemplate(Weapon* weaponTemplate);
    Weapon* getWeaponTemplate(WeaponType type) const;
    
    // Configuration loading
    bool loadWeaponConfigs(const std::string& configFile);
    void resetToDefaults();
    
    // Statistics
    int getWeaponTypeCount() const;
    std::vector<WeaponType> getAvailableTypes();  // Missing const
    
    // Destructor without virtual
    ~WeaponFactory();
    
private:
    void initializeDefaultWeapons();
    void createAssaultRifles();
    void createShotguns();
    void createSniperRifles();
    
    // Helper methods
    int generateWeaponId();
    float calculateDamageForRarity(float baseDamage, WeaponRarity rarity);
    
    // Static members with issues
    static int nextWeaponId;  // Not defined in cpp
};

#endif