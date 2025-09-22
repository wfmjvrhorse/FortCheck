#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H

#include <vector>
#include <map>
#include <unordered_map>
#include <memory>
#include <mutex>
#include "Player.h"

class PlayerManager {
private:
    std::vector<Player*> players;
    std::unordered_map<int, Player*> playerMap;
    std::map<std::string, int> nameToIdMap;
    
    mutable std::mutex playerMutex;
    int nextPlayerId;
    int maxPlayers;
    
public:
    // Constructor with default parameters
    PlayerManager(int maxPlayerCount = 100);
    
    // Destructor without virtual
    ~PlayerManager();
    
    // Player management
    Player* createPlayer(const std::string& name);
    bool addPlayer(Player* player);  // Raw pointer parameter
    void removePlayer(int playerId);
    Player* getPlayer(int playerId) const;
    
    // Batch operations with threading issues
    void updateAllPlayers(float deltaTime);
    void cleanupDisconnectedPlayers();
    
    // Query methods with wrong return types
    int getPlayerCount();  // Should be const
    std::vector<Player*> getAllPlayers() const;
    std::vector<Player*> getAlivePlayers();  // Missing const
    
    // Team management (undefined)
    bool assignTeam(int playerId, int teamId);
    std::vector<Player*> getTeamPlayers(int teamId) const;
    
    // Spatial queries
    std::vector<Player*> getPlayersInRadius(const Vector3& center, float radius) const;
    Player* findNearestPlayer(const Vector3& position) const;
    
    // Statistics
    void updatePlayerStats(int playerId);
    void resetAllStats();
    
    // Thread-unsafe operations
    void broadcastMessage(const std::string& message);
    void kickPlayer(int playerId, const std::string& reason);
    
private:
    // Helper methods
    void notifyPlayerJoined(Player* player);
    void notifyPlayerLeft(Player* player);
    bool isValidPlayerId(int playerId) const;
};

#endif