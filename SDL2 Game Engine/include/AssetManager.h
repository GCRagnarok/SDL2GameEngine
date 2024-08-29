#pragma once
#include <map>
#include <string>
#include <vector>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

class Manager;
class Entity;
class Vector2D;
class UILabelComponent;
class Map;
class Physics;

class AssetManager
{
public:
	AssetManager(Manager* p_Manager, Physics* p_Physics);
	~AssetManager();

	enum GroupLabels : std::size_t
	{
		groupTiles,
		groupPlayers,
		groupColliders,
		groupProjectiles,
		groupPickups,
		groupMaps,
		groupUILabels
	};

	// GameObjects
	Entity* CreatePlayer(Vector2D p_Pos, int p_TileSize, int p_Scale, const std::string p_TextureID, bool isAnimated, UILabelComponent* p_ScoreLabel);
	void CreateCoin(Vector2D p_Pos, int p_TileSize, int p_Scale, const std::string p_TextureID, bool isAnimated, const std::string p_AudioID, Mix_Chunk* p_MixChunkName);
	void CreateMusicPlayer(const std::string p_MusicID, Mix_Music* p_Music, bool p_PlayOnInit, int loop);

	// Map
	void CreateMap(const char* p_MapFilePath, const std::string p_TextureID, int p_MapSizeX, int p_MapSizeY, int p_TileSize, int p_SSTilePerRow, int p_MapScale);

	// UI
	UILabelComponent* CreateUILabel(int p_XPos, int p_YPos, const std::string p_Text, const std::string p_Font, SDL_Colour& p_Colour);

	// Texture Management
	void AddTexture(const std::string p_TextureID, const char* p_Path);
	SDL_Texture* GetTexture(const std::string p_TextureID);

	// Font Management
	void AddFont(const std::string p_FontID, const std::string p_Path, int p_FontSize);
	TTF_Font* GetFont(const std::string p_FontID);
	void CleanAssets();

	// Audio Management
	Mix_Music* AddMusic(const std::string p_MusicID, const char* p_Path);
	Mix_Music* GetMusic(const std::string p_MusicID);

	Mix_Chunk* AddSound(const std::string p_SoundID, const char* p_Path);
	Mix_Chunk* GetSound(const std::string p_SoundID);

	void DrawAssets();

private:
	Manager* m_Manager;
	Physics* m_Physics;
	Map* m_Map;

	std::map<const std::string, SDL_Texture*> m_Textures;
	std::map<const std::string, TTF_Font*> m_Fonts;
	std::map<const std::string, Mix_Music*> m_MusicTracks;
	std::map<const std::string, Mix_Chunk*> m_Sounds;

	std::vector<Entity*>& g_TileGroup;
	std::vector<Entity*>& g_PlayerGroup;
	std::vector<Entity*>& g_ColliderGroup;
	std::vector<Entity*>& g_PickupGroup;
	std::vector<Entity*>& g_MapGroup;
	std::vector<Entity*>& g_UILabelGroup;
};