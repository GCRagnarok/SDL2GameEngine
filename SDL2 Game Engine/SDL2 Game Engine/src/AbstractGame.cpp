#include <iostream>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include "../include/AbstractGame.h"
#include "../include/AssetManager.h"

const int AbstractGame::s_WindowWidth;
const int AbstractGame::s_WindowHeight;
SDL_Renderer* AbstractGame::s_Renderer = nullptr;
SDL_Event AbstractGame::s_Event;
bool AbstractGame::s_IsRunnning = false;

AbstractGame::AbstractGame()
{
    m_Window = nullptr;
    m_DeltaTime = 0.0f;
}

AbstractGame::~AbstractGame()
{
}

void AbstractGame::Init(const char* p_Title, int p_XPos, int p_YPos, int p_Width, int p_Height, bool p_Fullscreen)
{
    int flags = 0;

    if (p_Fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    // Initialize SDL and create window and renderer
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        m_Window = SDL_CreateWindow(p_Title, p_XPos, p_YPos, p_Width, p_Height, flags);
        s_Renderer = SDL_CreateRenderer(m_Window, -1, 0);

        if (s_Renderer)
        {
            SDL_SetRenderDrawColor(s_Renderer, 255, 255, 255, 255);
        }

        s_IsRunnning = true;
    }

    // Initialize SDL_Mixer for audio support
    if (Mix_Init(MIX_INIT_MP3) != MIX_INIT_MP3)
    {
        std::cout << "Error : SDL_Mixer initialisation failed" << std::endl;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1)
    {
        std::cout << "Error : SDL_Mixer - audio device - initialisation failed" << std::endl;
    }

    // Initialize SDL_TTF for font support
    if (TTF_Init() == -1)
    {
        std::cout << "Error : SDL_TTF" << std::endl;
    }

    LoadGame();
}

void AbstractGame::HandleEvents()
{
    SDL_PollEvent(&s_Event);
    switch (s_Event.type)
    {
    case SDL_QUIT:
        s_IsRunnning = false;
        break;
    }
}

void AbstractGame::Clean()
{
    s_Assets->CleanAssets();

    SDL_DestroyWindow(m_Window);
    SDL_DestroyRenderer(s_Renderer);
    Mix_CloseAudio();
    Mix_Quit();
    TTF_Quit();
    SDL_Quit();
}

int AbstractGame::RunMainLoop()
{
    Init("ChurchEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, s_WindowWidth, s_WindowHeight, false);

    Uint64 frameStart, frameEnd;
    double frameTime;

    while (s_IsRunnning)
    {
        frameStart = SDL_GetPerformanceCounter();

        HandleEvents();
        Update();
        Render();

        frameEnd = SDL_GetPerformanceCounter();
        frameTime = (frameEnd - frameStart) / static_cast<double>(SDL_GetPerformanceFrequency());

        // Calculate the time to delay to cap the frame rate
        if (m_frameDelay > frameTime * 1000.0)
        {
            SDL_Delay(static_cast<Uint32>(m_frameDelay - frameTime * 1000.0));
        }

        // Recalculate frameEnd and frameTime after the delay
        frameEnd = SDL_GetPerformanceCounter();
        frameTime = (frameEnd - frameStart) / static_cast<double>(SDL_GetPerformanceFrequency());
        m_DeltaTime = static_cast<float>(frameTime);
    }

    Clean();

    return 0;
}