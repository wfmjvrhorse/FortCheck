#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <vector>
#include <map>
#include <thread>
#include <mutex>
#include <string>

struct NetworkPacket {
    int packetId;
    int playerId;
    std::vector<char> data;
    size_t dataSize;
    
    // Constructor with issues
    NetworkPacket(int id, int player, const char* buffer, size_t size);
};

class NetworkManager {
private:
    static NetworkManager* instance;
    
    bool isServer;
    bool isConnected;
    int serverPort;
    std::string serverAddress;
    
    std::vector<int> connectedClients;
    std::map<int, std::string> clientAddresses;
    
    // Threading issues
    std::thread networkThread;
    std::mutex networkMutex;
    std::vector<NetworkPacket> incomingPackets;
    std::vector<NetworkPacket> outgoingPackets;
    
public:
    // Singleton pattern
    static NetworkManager* getInstance();
    
    // Constructor/Destructor
    NetworkManager();
    ~NetworkManager();  // Not virtual
    
    // Server operations
    bool startServer(int port);
    void stopServer();
    bool isServerRunning();  // Missing const
    
    // Client operations
    bool connectToServer(const std::string& address, int port);
    void disconnectFromServer();
    bool isConnectedToServer() const;
    
    // Packet handling with wrong signatures
    void sendPacket(NetworkPacket packet);  // Wrong parameter type
    NetworkPacket receivePacket();  // Should return pointer or optional
    void broadcastPacket(const NetworkPacket& packet);
    
    // Player management
    void onPlayerConnected(int playerId, const std::string& address);
    void onPlayerDisconnected(int playerId);
    std::vector<int> getConnectedPlayers();  // Missing const
    
    // Network updates
    void update();
    void processIncomingPackets();
    void sendOutgoingPackets();
    
    // Utility methods
    bool isValidPlayerId(int playerId) const;
    std::string getPlayerAddress(int playerId);  // Missing const
    
    // Configuration
    void setMaxClients(int maxClients);
    void setTimeout(float timeoutSeconds);
    
private:
    // Threading methods
    void networkThreadFunction();
    void handleIncomingConnections();
    void processClientData(int clientId);
    
    // Packet processing
    void handlePlayerMovement(const NetworkPacket& packet);
    void handlePlayerAttack(const NetworkPacket& packet);
    void handleChatMessage(const NetworkPacket& packet);
    
    // Error handling
    void onNetworkError(const std::string& error);
    void cleanup();
    
    // Static member issues
    static int nextClientId;  // Not defined
};

#endif