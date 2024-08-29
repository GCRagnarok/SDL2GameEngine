#pragma once
#include <SDL_mixer.h>
#include "EntityComponentSystem.h"

class AudioComponent : public Component
{
public:
    enum class AudioType
    {
        MUSIC,
        SOUND
    };

    AudioComponent(const std::string& p_MusicID, Mix_Music* music) : m_MusicID(p_MusicID), m_AudioType(AudioType::MUSIC)
    {
        m_Audio.m_Music = music;
    }

    AudioComponent(const std::string& p_SoundID, Mix_Chunk* sound) : m_MusicID(p_SoundID), m_AudioType(AudioType::SOUND)
    {
        m_Audio.m_Sound = sound;
    }

    ~AudioComponent()
    {

    }

    // Music
    static Mix_Music* LoadMusic(const std::string p_MusicID)
    {
        Mix_Music* music = Mix_LoadMUS(p_MusicID.c_str());
        if (!music)
        {
            std::cout << "Failed to load music file: " + p_MusicID << " " << Mix_GetError() << std::endl;
        }
        return music;
    }

    void PlayMusic(Mix_Music* p_MusicFile, int loopCount)
    {
        Mix_PlayMusic(p_MusicFile, loopCount);
    }

    // Sounds
    static Mix_Chunk* LoadSound(const std::string p_SoundID)
    {
        Mix_Chunk* sound = Mix_LoadWAV(p_SoundID.c_str());
        if (!sound)
        {
            std::cout << "Failed to load music file: " + p_SoundID << " " << Mix_GetError() << std::endl;
        }
        return sound;
    }

    void PlaySound(Mix_Chunk* p_SoundID, int channel, int loopCount)
    {
        Mix_PlayChannel(channel, p_SoundID, loopCount);
    }

private:

    const std::string m_MusicID;
    const std::string m_SoundID;
    AudioType m_AudioType;

    union
    {
        Mix_Music* m_Music;
        Mix_Chunk* m_Sound;
    }m_Audio;
};