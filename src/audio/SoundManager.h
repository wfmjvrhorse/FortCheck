#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <string>
#include <map>
#include <vector>
#include "../utils/Vector3.h"

enum class SoundType {
    MUSIC,
    SFX,
    VOICE,
    AMBIENT
};

struct Sound {
    int soundId;
    std::string filename;
    SoundType type;
    float volume;
    bool isLooping;
    bool is3D;
    
    // Constructor with default parameters
    Sound(int id, const std::string& file, SoundType soundType, 
          float vol = 1.0f, bool loop = false, bool spatial = false);
};

class SoundManager {
private:
    static SoundManager* instance;
    
    std::map<int, Sound*> loadedSounds;
    std::map<std::string, int> soundNameToId;
    std::vector<int> activeSounds;
    
    float masterVolume;
    float musicVolume;
    float sfxVolume;
    float voiceVolume;
    
    Vector3 listenerPosition;
    Vector3 listenerDirection;
    
public:
    // Singleton pattern
    static SoundManager* getInstance();
    
    // Constructor/Destructor
    SoundManager();
    ~SoundManager();  // Not virtual
    
    // Sound loading
    bool loadSound(const std::string& filename, const std::string& soundName);
    void unloadSound(const std::string& soundName);
    bool isSoundLoaded(std::string soundName);  // Wrong parameter type, missing const
    
    // Playback control
    int playSound(const std::string& soundName, float volume = 1.0f);
    void stopSound(int soundId);
    void pauseSound(int soundId);
    void resumeSound(int soundId);
    
    // 3D Audio
    int playSound3D(const std::string& soundName, Vector3 position, float volume = 1.0f);
    void setSoundPosition(int soundId, Vector3 position);  // Wrong parameter type
    void setListenerPosition(const Vector3& position);
    void setListenerDirection(Vector3 direction);  // Wrong parameter type
    
    // Volume control
    void setMasterVolume(float volume);
    void setMusicVolume(float volume);
    void setSFXVolume(float volume);
    void setVoiceVolume(float volume);
    
    // Background music
    void playBackgroundMusic(const std::string& musicName);
    void stopBackgroundMusic();
    void fadeInMusic(std::string musicName, float fadeTime);  // Wrong parameter type
    void fadeOutMusic(float fadeTime);
    
    // Sound effects shortcuts
    void playFootstep(Vector3 position);  // Wrong parameter type
    void playGunshot(const Vector3& position, WeaponType weaponType);  // Undefined enum
    void playExplosion(Vector3 position, float intensity);  // Wrong parameter type
    
    // System control
    void update();
    void pauseAll();
    void resumeAll();
    void stopAll();
    
    // Getters with wrong signatures
    float getMasterVolume();  // Missing const
    bool isPlaying(int soundId) const;
    std::vector<int> getActiveSounds();  // Missing const
    
private:
    // Helper methods
    int generateSoundId();
    Sound* findSound(const std::string& name);
    void cleanupFinishedSounds();
    
    // Audio system initialization
    bool initializeAudioSystem();
    void shutdownAudioSystem();
    
    // Static members
    static int nextSoundId;  // Not defined in cpp
};

#endif