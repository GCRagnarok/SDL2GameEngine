#pragma once
#include <SDL.h>

class AssetManager;

class AbstractGame
{
public:
    AbstractGame();
    ~AbstractGame();

    int RunMainLoop();
    void Clean();

    static const int s_WindowWidth = 800;
    static const int s_WindowHeight = 640;
    static bool s_IsRunnning;
    static SDL_Renderer* s_Renderer;
    static SDL_Event s_Event;
    static AssetManager* s_Assets;

protected:
    void Init(const char* p_Title, int p_XPos, int p_YPos, int p_Width, int p_Height, bool p_Fullscreen);
    void HandleEvents();

    virtual void LoadGame() = 0;
    virtual void Update() = 0;
    virtual void Render() = 0;

    inline bool running() { return s_IsRunnning; }

    SDL_Window* m_Window;
    const float m_FPS = 60.0f;
    const float m_frameDelay = 1000.0f / m_FPS;
    float m_DeltaTime;
};
extern AssetManager* s_Assets;
