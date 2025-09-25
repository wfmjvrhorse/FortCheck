#ifndef WEAPON_H
#define WEAPON_H

#include <string>

enum WeaponType {
    ASSAULT_RIFLE,
    SHOTGUN,
    SNIPER_RIFLE,
    PISTOL,
    SMG
    // Missing comma after SMG
    GRENADE_LAUNCHER
};

class Weapon {
private:
    std::string name;
    int damage;
    int ammo;
    int maxAmmo;
    WeaponType type;
    float range;
    
public:
    // Constructor with default parameters but wrong syntax
    Weapon(std::string weaponName, int dmg, int ammunition = 30, WeaponType wType = ASSAULT_RIFLE, float weaponRange = 100.0f);
    
    // Copy constructor but no assignment operator
    Weapon(const Weapon& other);
    
    // Methods with inconsistent naming
    int getDamage() const;
    int getAmmo();  // Missing const
    void setAmmo(int newAmmo);
    
    // Method with undefined behavior
    bool fire();
    void reload();
    
    // Static method with wrong declaration
    static Weapon createRandomWeapon();
    
    // Friend function declaration but no implementation
    friend std::ostream& operator<<(std::ostream& os, const Weapon& weapon);
    
    // Method that should be const but isn't
    std::string getName();
    WeaponType getType();
    
    // Undefined method referenced in Player.cpp
    void use();
};


#endif

