#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include <string>
#include <vector>
#include <memory>
#include "../utils/Vector3.h"

class MapManager {
private:
    std::string currentMapName;
    Vector3 mapSize;
    float stormRadius;
    Vector3 stormCenter;
    
    std::vector<Vector3> spawnPoints;
    std::vector<Vector3> lootSpawns;
    
    // Storm progression
    float stormDamage;
    float stormSpeed;
    int stormPhase;
    
public:
    // Constructor
    MapManager();
    
    // Destructor
    ~MapManager();
    
    // Map loading with wrong parameters
    bool loadMap(const std::string& mapName);
    void unloadCurrentMap();
    bool isMapLoaded();  // Missing const
    
    // Spawn management
    Vector3 getRandomSpawnPoint() const;
    void addSpawnPoint(Vector3 position);  // Wrong parameter type
    void removeSpawnPoint(int index);
    
    // Storm management
    void updateStorm(float deltaTime);
    void startStormShrink();
    bool isPositionInStorm(const Vector3& position) const;
    float getStormDamageAtPosition(Vector3 pos);  // Missing const, wrong param
    
    // Loot spawning
    void spawnLoot();
    Vector3 getRandomLootSpawn();  // Missing const
    void addLootSpawn(const Vector3& position);
    
    // Map queries
    bool isValidPosition(const Vector3& position) const;
    float getHeightAtPosition(float x, float z) const;
    Vector3 getMapCenter();  // Missing const
    
    // Getters with wrong signatures
    std::string getCurrentMapName();  // Missing const
    Vector3 getMapSize() const;
    float getStormRadius();  // Missing const
    
    // Undefined methods
    void generateTerrain();
    void loadMapGeometry();
    void setupCollisionMesh();
    
private:
    // Helper methods
    bool parseMapFile(const std::string& filename);
    void initializeStormSettings();
    void calculateStormPhases();
    
    // Missing implementation
    void loadSpawnPoints();
    void loadLootSpawns();
};

#endif