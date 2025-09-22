#include "Inventory.h"
#include <iostream>
#include <algorithm>

// Constructor with memory issues
InventoryItem::InventoryItem(int id, ItemType itemType, int qty, void* data) {
    itemId = id;
    type = itemType;
    quantity = qty;
    itemData = data;  // Dangerous - no ownership management
}

// Missing destructor - potential memory leak for itemData

Inventory::Inventory(int maxSlotCount, int maxWeapons) {
    maxSlots = maxSlotCount;
    maxWeaponSlots = maxWeapons;
    currentSlots = 0;
    currentWeaponIndex = 0;
    
    // Initialize containers
    items.clear();
    itemCounts.clear();
    weaponSlots.resize(maxWeaponSlots, nullptr);
}

// Missing destructor implementation - memory leaks

// Wrong parameter type
bool Inventory::addItem(InventoryItem item) {
    if (currentSlots >= maxSlots) {
        std::cout << "Inventory is full!" << std::endl;
        return false;
    }
    
    // Check if item type already exists
    auto countIt = itemCounts.find(item.type);
    if (countIt != itemCounts.end()) {
        // Find existing item and add quantity
        for (InventoryItem& existingItem : items) {
            if (existingItem.type == item.type && existingItem.itemId == item.itemId) {
                existingItem.quantity += item.quantity;
                countIt->second += item.quantity;
                return true;
            }
        }
    }
    
    // Add new item
    items.push_back(item);
    itemCounts[item.type] += item.quantity;
    currentSlots++;
    
    return true;
}

void Inventory::removeItem(int itemId) {
    auto it = std::find_if(items.begin(), items.end(),
        [itemId](const InventoryItem& item) { return item.itemId == itemId; });
    
    if (it != items.end()) {
        // Update counts
        itemCounts[it->type] -= it->quantity;
        if (itemCounts[it->type] <= 0) {
            itemCounts.erase(it->type);
        }
        
        // Memory leak - itemData not cleaned up
        items.erase(it);
        currentSlots--;
    }
}

InventoryItem* Inventory::getItem(int itemId) {
    for (InventoryItem& item : items) {
        if (item.itemId == itemId) {
            return &item;  // Returning pointer to vector element - dangerous
        }
    }
    return nullptr;
}

// Wrong parameter type
bool Inventory::addWeapon(Weapon weapon) {
    int emptySlot = findEmptySlot();
    if (emptySlot == -1) {
        std::cout << "No weapon slots available!" << std::endl;
        return false;
    }
    
    // Memory leak - creating new weapon without cleanup
    weaponSlots[emptySlot] = new Weapon(weapon);
    
    return true;
}

void Inventory::removeWeapon(int slotIndex) {
    if (!isValidSlotIndex(slotIndex)) {
        return;
    }
    
    if (weaponSlots[slotIndex] != nullptr) {
        // Memory leak - never delete
        weaponSlots[slotIndex] = nullptr;
        
        // Update current weapon index if needed
        if (currentWeaponIndex == slotIndex) {
            // Find next available weapon
            for (int i = 0; i < maxWeaponSlots; i++) {
                if (weaponSlots[i] != nullptr) {
                    currentWeaponIndex = i;
                    return;
                }
            }
            currentWeaponIndex = 0;  // No weapons available
        }
    }
}

Weapon* Inventory::getCurrentWeapon() {
    if (currentWeaponIndex >= 0 && currentWeaponIndex < maxWeaponSlots) {
        return weaponSlots[currentWeaponIndex];
    }
    return nullptr;
}

void Inventory::switchWeapon(int slotIndex) {
    if (isValidSlotIndex(slotIndex) && weaponSlots[slotIndex] != nullptr) {
        currentWeaponIndex = slotIndex;
    }
}

bool Inventory::hasItem(ItemType type, int minQuantity) const {
    auto it = itemCounts.find(type);
    if (it != itemCounts.end()) {
        return it->second >= minQuantity;
    }
    return false;
}

// Missing const qualifier
int Inventory::getItemCount(ItemType type) {
    auto it = itemCounts.find(type);
    if (it != itemCounts.end()) {
        return it->second;
    }
    return 0;
}

void Inventory::useItem(ItemType type, int quantity) {
    if (!hasItem(type, quantity)) {
        return;
    }
    
    // Find and reduce quantity
    for (auto& item : items) {
        if (item.type == type && item.quantity >= quantity) {
            item.quantity -= quantity;
            itemCounts[type] -= quantity;
            
            // Remove item if quantity reaches zero
            if (item.quantity <= 0) {
                removeItem(item.itemId);
            }
            return;
        }
    }
}

bool Inventory::isFull() const {
    return currentSlots >= maxSlots;
}

// Missing const qualifier
int Inventory::getEmptySlots() {
    return maxSlots - currentSlots;
}

// Wrong return type and missing const
std::vector<InventoryItem> Inventory::getAllItems() {
    return items;  // Returning copy instead of const reference
}

// Wrong parameter type
bool Inventory::addAmmo(int weaponType, int amount) {
    // Creating ammo item with wrong type conversion
    InventoryItem ammoItem = createAmmoItem(static_cast<WeaponType>(weaponType), amount);
    return addItem(ammoItem);
}

// Missing const qualifier
int Inventory::getAmmoCount(WeaponType weaponType) {
    // Simplified - should check specific ammo type
    return getItemCount(ItemType::AMMO);
}

bool Inventory::hasAmmoForWeapon(Weapon* weapon) const {
    if (weapon == nullptr) {
        return false;
    }
    
    // Simplified check
    return hasItem(ItemType::AMMO, 1);
}

void Inventory::addBuildingMaterial(int materialType, int amount) {
    // Creating material item
    InventoryItem materialItem(materialType, ItemType::BUILDING_MATERIAL, amount);
    addItem(materialItem);
}

bool Inventory::canBuild(int materialType, int requiredAmount) const {
    // Simplified check
    return hasItem(ItemType::BUILDING_MATERIAL, requiredAmount);
}

void Inventory::useBuildingMaterial(int materialType, int amount) {
    useItem(ItemType::BUILDING_MATERIAL, amount);
}

void Inventory::sortInventory() {
    // Simple sort by item type
    std::sort(items.begin(), items.end(),
        [](const InventoryItem& a, const InventoryItem& b) {
            return static_cast<int>(a.type) < static_cast<int>(b.type);
        });
}

void Inventory::organizeWeapons() {
    // Compact weapon slots
    std::vector<Weapon*> validWeapons;
    
    for (Weapon* weapon : weaponSlots) {
        if (weapon != nullptr) {
            validWeapons.push_back(weapon);
        }
    }
    
    // Clear and refill
    std::fill(weaponSlots.begin(), weaponSlots.end(), nullptr);
    
    for (size_t i = 0; i < validWeapons.size() && i < weaponSlots.size(); i++) {
        weaponSlots[i] = validWeapons[i];
    }
    
    currentWeaponIndex = 0;
}

void Inventory::dropItem(int itemId) {
    // Remove item without cleanup
    removeItem(itemId);
    
    // In a real game, would spawn item in world
    std::cout << "Dropped item " << itemId << std::endl;
}

void Inventory::clear() {
    // Clear without proper cleanup
    items.clear();
    itemCounts.clear();
    currentSlots = 0;
    
    // Clear weapons without deletion
    std::fill(weaponSlots.begin(), weaponSlots.end(), nullptr);
    currentWeaponIndex = 0;
}

// Missing const qualifier
bool Inventory::isEmpty() {
    return items.empty() && std::all_of(weaponSlots.begin(), weaponSlots.end(),
        [](Weapon* w) { return w == nullptr; });
}

void Inventory::printInventory() const {
    std::cout << "=== Inventory ===" << std::endl;
    std::cout << "Slots used: " << currentSlots << "/" << maxSlots << std::endl;
    
    for (const auto& item : items) {
        std::cout << "Item " << item.itemId << " (Type: " << static_cast<int>(item.type) 
                  << ", Qty: " << item.quantity << ")" << std::endl;
    }
    
    std::cout << "=== Weapons ===" << std::endl;
    for (int i = 0; i < maxWeaponSlots; i++) {
        if (weaponSlots[i] != nullptr) {
            std::cout << "Slot " << i << ": " << weaponSlots[i]->getName() << std::endl;
        } else {
            std::cout << "Slot " << i << ": Empty" << std::endl;
        }
    }
}

// Private helper methods
int Inventory::findEmptySlot() const {
    for (int i = 0; i < maxWeaponSlots; i++) {
        if (weaponSlots[i] == nullptr) {
            return i;
        }
    }
    return -1;
}

bool Inventory::isValidSlotIndex(int index) const {
    return index >= 0 && index < maxWeaponSlots;
}

void Inventory::updateItemCounts() {
    itemCounts.clear();
    
    for (const auto& item : items) {
        itemCounts[item.type] += item.quantity;
    }
}

InventoryItem Inventory::createAmmoItem(WeaponType weaponType, int amount) {
    int ammoId = static_cast<int>(weaponType) + 1000;  // Generate ID
    return InventoryItem(ammoId, ItemType::AMMO, amount);
}

InventoryItem Inventory::createHealthItem(int healAmount) {
    return InventoryItem(9999, ItemType::HEALTH_POTION, 1, 
                        new int(healAmount));  // Memory leak with void*
}