#include "../include/Game.h"
#include "../include/ECS/EntityComponentSystem.h"
#include "../include/ECS/UILabelComponent.h"
#include "../include/GameStateManager.h"
#include "../include/Physics.h"

Manager g_Manager;
Physics g_Physics;
AssetManager* AbstractGame::s_Assets = new AssetManager(&g_Manager, &g_Physics);

// Constructor: Creates a new GameStateManager with a reference to the global manager.
Game::Game() : m_Player(nullptr), m_ScoreLabel(nullptr)
{
    m_GameStateManager = new GameStateManager(this, &g_Manager, 50);
}

Game::~Game()
{
    delete m_GameStateManager;
}

void Game::LoadGame()
{
	// Clear the manager and assets
    g_Manager.Clear();
    s_Assets->CleanAssets();

    // Load textures
    s_Assets->AddTexture("platformerMap", "assets/sprites/platformerMap_ss.png");
    s_Assets->AddTexture("player", "assets/sprites/player_anims.png");
    s_Assets->AddTexture("coin", "assets/sprites/coin_anims.png");

    // Load fonts
    s_Assets->AddFont("pixel", "assets/fonts/Little Malio 8-Bit.otf", 16);

    // Load audio
    Mix_Music* BackgroundMusic = s_Assets->AddMusic("bgMusic", "assets/audio/music/backgroundMusic.wav");
    Mix_Chunk* pickupSound = s_Assets->AddSound("pickup_sound", "assets/audio/sounds/pickup.wav");

    // Create map
    s_Assets->CreateMap("assets/maps/platformerMap.map", "platformerMap", 25, 20, 8, 10, 4);

    // Create UI label for score
    SDL_Color red = { 255, 0, 0, 255 };
    m_ScoreLabel = s_Assets->CreateUILabel(675, 10, " ", "pixel", red);

    // Create game objects
    s_Assets->CreateMusicPlayer("bgMusic", BackgroundMusic, true, -1);
    m_Player = s_Assets->CreatePlayer(Vector2D(200, 400), 16, 2, "player", true, m_ScoreLabel);
    s_Assets->CreateCoin(Vector2D(50, 320), 8, 2, "coin", true, "pickup_sound", pickupSound);
    s_Assets->CreateCoin(Vector2D(375, 250), 8, 2, "coin", true, "pickup_sound", pickupSound);
    s_Assets->CreateCoin(Vector2D(660, 505), 8, 2, "coin", true, "pickup_sound", pickupSound);
    s_Assets->CreateCoin(Vector2D(615, 120), 8, 2, "coin", true, "pickup_sound", pickupSound);
    s_Assets->CreateCoin(Vector2D(100, 20), 8, 2, "coin", true, "pickup_sound", pickupSound);
}

void Game::Update()
{
    m_GameStateManager->Update();
    g_Physics.SetDeltaTime(m_DeltaTime);
}

void Game::Render()
{
    SDL_RenderClear(s_Renderer);
    s_Assets->DrawAssets();
    SDL_RenderPresent(s_Renderer);
}