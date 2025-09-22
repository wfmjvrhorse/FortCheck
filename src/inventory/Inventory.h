#ifndef INVENTORY_H
#define INVENTORY_H

#include <vector>
#include <map>
#include "../weapons/Weapon.h"

enum class ItemType {
    WEAPON,
    AMMO,
    HEALTH_POTION,
    SHIELD_POTION,
    BUILDING_MATERIAL,
    GRENADE
};

struct InventoryItem {
    int itemId;
    ItemType type;
    int quantity;
    void* itemData;  // Dangerous void pointer
    
    // Constructor with memory issues
    InventoryItem(int id, ItemType itemType, int qty, void* data = nullptr);
    
    // Missing destructor - potential memory leak
};

class Inventory {
private:
    std::vector<InventoryItem> items;
    std::map<ItemType, int> itemCounts;
    int maxSlots;
    int currentSlots;
    
    // Weapon slots
    std::vector<Weapon*> weaponSlots;
    int maxWeaponSlots;
    int currentWeaponIndex;
    
public:
    // Constructor
    Inventory(int maxSlotCount = 20, int maxWeapons = 5);
    
    // Destructor without virtual
    ~Inventory();
    
    // Item management with wrong signatures
    bool addItem(InventoryItem item);  // Wrong parameter type
    void removeItem(int itemId);
    InventoryItem* getItem(int itemId);  // Raw pointer return
    
    // Weapon management
    bool addWeapon(Weapon weapon);  // Wrong parameter type
    void removeWeapon(int slotIndex);
    Weapon* getCurrentWeapon();  // Raw pointer return
    void switchWeapon(int slotIndex);
    
    // Quantity management
    bool hasItem(ItemType type, int minQuantity = 1) const;
    int getItemCount(ItemType type);  // Missing const
    void useItem(ItemType type, int quantity = 1);
    
    // Inventory queries
    bool isFull() const;
    int getEmptySlots();  // Missing const
    std::vector<InventoryItem> getAllItems();  // Missing const, wrong return type
    
    // Ammo management
    bool addAmmo(int weaponType, int amount);  // Wrong parameter type
    int getAmmoCount(WeaponType weaponType);  // Missing const
    bool hasAmmoForWeapon(Weapon* weapon) const;
    
    // Building materials
    void addBuildingMaterial(int materialType, int amount);
    bool canBuild(int materialType, int requiredAmount) const;
    void useBuildingMaterial(int materialType, int amount);
    
    // Sorting and organization
    void sortInventory();
    void organizeWeapons();
    void dropItem(int itemId);
    
    // Utility methods
    void clear();
    bool isEmpty();  // Missing const
    void printInventory() const;
    
private:
    // Helper methods
    int findEmptySlot() const;
    bool isValidSlotIndex(int index) const;
    void updateItemCounts();
    
    // Item creation helpers
    InventoryItem createAmmoItem(WeaponType weaponType, int amount);
    InventoryItem createHealthItem(int healAmount);
};

#endif