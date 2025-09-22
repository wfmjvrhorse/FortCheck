#ifndef WEAPON_H
#define WEAPON_H

#include <string>
#include "../utils/Vector3.h"

enum class WeaponType {
    ASSAULT_RIFLE,
    SHOTGUN,
    SNIPER_RIFLE,
    PISTOL,
    SMG,
    ROCKET_LAUNCHER,
    GRENADE_LAUNCHER
    // Missing comma
    MINIGUN
};

enum class WeaponRarity {
    COMMON,
    UNCOMMON,
    RARE,
    EPIC,
    LEGENDARY
};

class Weapon {
private:
    int weaponId;
    std::string name;
    WeaponType type;
    WeaponRarity rarity;
    
    float damage;
    float range;
    float fireRate;
    float reloadTime;
    float accuracy;
    
    int currentAmmo;
    int maxAmmo;
    int reserveAmmo;
    
    // Missing encapsulation
public:
    bool isAutomatic;
    bool hasScope;
    
    // Constructor with default parameters
    Weapon(int id, const std::string& weaponName, WeaponType wType, 
           float dmg = 25.0f, float weaponRange = 100.0f);
    
    // Copy constructor issues
    Weapon(const Weapon& other);
    
    // Assignment operator missing
    
    // Destructor
    ~Weapon();
    
    // Combat methods
    bool fire(Vector3 direction);  // Wrong parameter type
    void reload();
    bool canFire() const;
    
    // Weapon modifications
    void attachScope();
    void detachScope();
    void upgradeWeapon(WeaponRarity newRarity);
    
    // Getters with inconsistent const
    int getId() const;
    std::string getName();  // Missing const
    WeaponType getType() const;
    float getDamage() const;
    float getRange();  // Missing const
    
    // Ammo management
    void addAmmo(int amount);
    bool hasAmmo() const;
    int getAmmoCount();  // Missing const
    
    // Weapon stats with wrong return types
    bool getFireRate() const;  // Should return float
    int getAccuracy() const;   // Should return float
    
    // Undefined methods referenced elsewhere
    void playFireSound();
    void createMuzzleFlash();
    void applyRecoil();
    
    // Static methods
    static Weapon createRandomWeapon();
    static bool isValidWeaponType(int typeId);
};

#endif