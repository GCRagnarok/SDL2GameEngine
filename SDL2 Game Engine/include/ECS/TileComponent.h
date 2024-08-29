#pragma once
#include "EntityComponentSystem.h"
#include "../Vector2D.h"
#include "../TextureManager.h"
#include "../AssetManager.h"
#include "../Game.h"

class Game;

class TileComponent : public Component
{
public:
	SDL_Texture* m_Texture = nullptr;
	SDL_Rect m_SrcRect = { 0,0,0,0 };
	SDL_Rect m_DstRect = { 0,0,0,0 };
	Vector2D m_Position;

	TileComponent() = default;

	~TileComponent()
	{
		SDL_DestroyTexture(m_Texture);
	}

	TileComponent(int p_SrcX, int p_SrcY, int p_XPos, int p_YPos, int p_TileSize, int p_TileScale, const std::string p_TextureID)
	{
		m_Texture = Game::s_Assets->GetTexture(p_TextureID);

		m_Position.m_X = static_cast<float>(p_XPos);
		m_Position.m_Y = static_cast<float>(p_YPos);

		m_SrcRect.x = static_cast<int>(p_SrcX);
		m_SrcRect.y = static_cast<int>(p_SrcY);
		m_SrcRect.w = m_SrcRect.h = static_cast<int>(p_TileSize);

		m_DstRect.x = static_cast<int>(p_XPos);
		m_DstRect.y = static_cast<int>(p_YPos);
		m_DstRect.w = m_DstRect.h = static_cast<int>(p_TileSize * p_TileScale);
	}

	void Draw() override
	{
		TextureManager::Draw(m_Texture, m_SrcRect, m_DstRect, SDL_FLIP_NONE);
	}

};
