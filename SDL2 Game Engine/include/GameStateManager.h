#pragma once
#include "ECS/Components.h"
#include "ECS/EntityComponentSystem.h"
#include <chrono>

class Game;

class GameStateManager
{
private:
    Game* m_Game;
    Manager* m_Manager;
    int m_ScoreThreshold;
    bool m_LoadingGame;
    std::chrono::time_point<std::chrono::steady_clock> m_LoadStartTime;
    std::chrono::milliseconds m_LoadDelay;

public:
    GameStateManager(Game* game, Manager* manager, int scoreThreshold, int loadDelayMs = 100)
        : m_Game(game), m_Manager(manager), m_ScoreThreshold(scoreThreshold), m_LoadingGame(false), m_LoadDelay(loadDelayMs) {}

    void Update()
    {
        // Refresh & Update manager
        m_Manager->Refresh();
        m_Manager->Update();

        // Check if the player's score has reached the threshold
        if (!m_LoadingGame && m_Game->GetPlayer()->GetComponent<PlayerComponent>().GetScore() >= m_ScoreThreshold)
        {
            m_LoadingGame = true;
            m_LoadStartTime = std::chrono::steady_clock::now();
        }

        // If loading game, check if delay has passed
        if (m_LoadingGame)
        {
            auto now = std::chrono::steady_clock::now();
            if (now - m_LoadStartTime >= m_LoadDelay)
            {
                m_Game->LoadGame();
                m_LoadingGame = false;
            }
        }
    }
};
