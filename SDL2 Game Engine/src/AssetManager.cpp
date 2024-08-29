#include "../include/AssetManager.h"
#include "../include/ECS/Components.h"
#include "../include/ECS/EntityComponentSystem.h"
#include "../include/Map.h"

// Constructor: Initializes manager, physics, and entity groups
AssetManager::AssetManager(Manager* p_Manager, Physics* p_Physics)
	: m_Manager(p_Manager), 
	m_Physics(p_Physics),
	g_TileGroup(m_Manager->GetGroup(groupTiles)),
	g_PlayerGroup(m_Manager->GetGroup(groupPlayers)),
	g_ColliderGroup(m_Manager->GetGroup(groupColliders)),
	g_PickupGroup(m_Manager->GetGroup(groupPickups)),
	g_MapGroup(m_Manager->GetGroup(groupMaps)),
	g_UILabelGroup(m_Manager->GetGroup(groupUILabels))
{
	m_Map = nullptr;
}

AssetManager::~AssetManager()
{

}

// Game Objects
Entity* AssetManager::CreatePlayer(Vector2D p_Pos, int p_TileSize, int p_Scale, const std::string p_TextureID, bool isAnimated, UILabelComponent* p_ScoreLabel)
{
	auto& player(m_Manager->AddEntity());
	player.AddComponent<TransformComponent>(p_Pos.m_X, p_Pos.m_Y, p_TileSize, p_TileSize, p_Scale);
	player.AddComponent<SpriteComponent>(p_TextureID, isAnimated);
	player.AddComponent<ColliderComponent>("player", p_TileSize);
	player.AddComponent<ScoreComponent>(p_ScoreLabel);
	player.AddComponent<Rigidbody2DComponent>(*m_Physics);
	player.AddComponent<PlayerComponent>(*m_Manager, p_ScoreLabel);
	player.AddGroup(groupPlayers);
	return &player;
}

void AssetManager::CreateCoin(Vector2D p_Pos, int p_TileSize, int p_Scale, const std::string p_TextureID, bool isAnimated, const std::string p_AudioID, Mix_Chunk* p_MixChunkName)
{
    auto& pickup(m_Manager->AddEntity());
    pickup.AddComponent<TransformComponent>(p_Pos.m_X, p_Pos.m_Y, p_TileSize, p_TileSize, p_Scale);
    pickup.AddComponent<SpriteComponent>(p_TextureID, true);
	pickup.AddComponent<ColliderComponent>("pickup", p_TileSize);
    pickup.AddComponent<AudioComponent>(p_AudioID, p_MixChunkName);
	pickup.AddComponent<PickupComponent>(p_TextureID);
    pickup.AddGroup(groupPickups);
}

void AssetManager::CreateMusicPlayer(const std::string p_MusicID, Mix_Music* p_Music, bool p_PlayOnInit, int loop)
{
	auto& musicPlayer(m_Manager->AddEntity());
	musicPlayer.AddComponent<AudioComponent>(p_MusicID, p_Music);
	if (p_PlayOnInit)
	{
		musicPlayer.GetComponent<AudioComponent>().PlayMusic(p_Music, loop);
	}

}

// Map management
void AssetManager::CreateMap(const char* p_MapFilePath, const std::string p_TextureID, int p_MapSizeX, int p_MapSizeY, int p_TileSize, int p_SSTilePerRow, int p_MapScale)
{
	m_Map = new Map(p_TextureID, p_MapScale, p_TileSize);
	m_Map->LoadMap(p_MapFilePath, p_MapSizeX, p_MapSizeY, p_SSTilePerRow);
}

// UI management
UILabelComponent* AssetManager::CreateUILabel(int p_XPos, int p_YPos, const std::string p_Text, const std::string p_Font, SDL_Colour& p_Colour)
{
	auto& label(m_Manager->AddEntity());
	label.AddComponent<UILabelComponent>(p_XPos, p_YPos, p_Text, p_Font, p_Colour);
	label.AddGroup(groupUILabels);
	return &label.GetComponent<UILabelComponent>();
}

// Texture management
void AssetManager::AddTexture(const std::string p_TextureID, const char* p_Path)
{
	m_Textures.emplace(p_TextureID, TextureManager::LoadTexture(p_Path));
}

SDL_Texture* AssetManager::GetTexture(const std::string p_TextureID)
{
	return m_Textures[p_TextureID];
}

// Font management
void AssetManager::AddFont(const std::string p_FontID, const std::string p_Path, int p_FontSize)
{
	m_Fonts.emplace(p_FontID, TTF_OpenFont(p_Path.c_str(), p_FontSize));
}

TTF_Font* AssetManager::GetFont(const std::string p_FontID)
{
	return m_Fonts[p_FontID];
}

// Music management
Mix_Music* AssetManager::AddMusic(const std::string p_MusicID, const char* p_Path)
{
	Mix_Music* music = AudioComponent::LoadMusic(p_Path);
	if (music == nullptr)
	{
		std::cout << "Failed to load music: " << Mix_GetError() << std::endl;
	}
	else
	{
		m_MusicTracks.emplace(p_MusicID, music);
	}
	return music;
}

Mix_Music* AssetManager::GetMusic(const std::string p_MusicID)
{
	return m_MusicTracks[p_MusicID];
}

// Sound management
Mix_Chunk* AssetManager::AddSound(const std::string p_SoundID, const char* p_Path)
{
	Mix_Chunk* sound = AudioComponent::LoadSound(p_Path);
	if (sound == nullptr)
	{
		std::cout << "Failed to load music: " << Mix_GetError() << std::endl;
	}
	else
	{
		m_Sounds.emplace(p_SoundID, sound);
	}
	return sound;
}

Mix_Chunk* AssetManager::GetSound(const std::string p_SoundID)
{
	return m_Sounds[p_SoundID];

}

// Asset lifecycle management
void AssetManager::DrawAssets()
{
	
	for (auto& t : g_TileGroup)
	{
		t->Draw();
	}
	for (auto& c : g_ColliderGroup)
	{
		c->Draw();
	}
	for (auto& p : g_PickupGroup)
	{
		p->Draw();
	}
	for (auto& p : g_PlayerGroup)
	{
		p->Draw();
	}
	for (auto& l : g_UILabelGroup)
	{
		l->Draw();
	}
}

void AssetManager::CleanAssets()
{

	for (auto& font : m_Fonts)
	{
		TTF_CloseFont(font.second);
	}
	m_Fonts.clear();


	for (auto& texture : m_Textures)
	{
		SDL_DestroyTexture(texture.second);
	}
	m_Textures.clear();


	for (auto& music : m_MusicTracks)
	{
		Mix_FreeMusic(music.second);
	}
	m_MusicTracks.clear();


	for (auto& sound : m_Sounds)
	{
		Mix_FreeChunk(sound.second);
	}
	m_Sounds.clear();
}