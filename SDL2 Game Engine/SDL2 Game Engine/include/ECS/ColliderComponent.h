#pragma once
#include <string>
#include <SDL.h>
#include "EntityComponentSystem.h"
#include "TransformComponent.h"
#include "../TextureManager.h"

class ColliderComponent : public Component
{
public:
	SDL_Rect m_Collider = { 0,0,0,0 };
	std::string m_Tag;

	SDL_Texture* m_Texture = nullptr;
	SDL_Rect m_SrcRect = { 0,0,0,0 };
	SDL_Rect m_DstRect = { 0,0,0,0 };

	TransformComponent* m_Transform = nullptr;

	bool m_drawCollider = false;

	ColliderComponent(const std::string& p_Tag, int p_Size)
		: m_Tag(p_Tag)
	{
		m_Collider.h = m_Collider.w = p_Size;
	}

	ColliderComponent(const std::string& p_Tag, int p_XPos, int p_Ypos, int p_Size)
		: m_Tag(p_Tag)
	{
		m_Collider.x = p_XPos;
		m_Collider.y = p_Ypos;
		m_Collider.h = m_Collider.w = p_Size;
	}
	
	void Init() override
	{
		if (!m_Entity->HasComponent<TransformComponent>())
		{
			m_Entity->AddComponent<TransformComponent>();
		}

		m_Transform = &m_Entity->GetComponent<TransformComponent>();
		m_Texture = TextureManager::LoadTexture("assets/sprites/coltex.png");
		m_SrcRect = {0, 0, m_Collider.w, m_Collider.h };
		m_DstRect = { m_Collider.x, m_Collider.y, m_Collider.w, m_Collider.h };
	}

	void Update() override
	{
		if (m_Tag != "mapColliders")
		{
			// Update colliders position and size based on the transform component.
			m_Collider.x = static_cast<int>(m_Transform->m_Position.m_X);
			m_Collider.y = static_cast<int>(m_Transform->m_Position.m_Y);
			m_Collider.w = m_Transform->m_Width * m_Transform->m_Scale;
			m_Collider.h = m_Transform->m_Height * m_Transform->m_Scale;
		}

		// Update the destination rectangle's position for rendering
		m_DstRect.x = m_Collider.x;
		m_DstRect.y = m_Collider.y;
		m_DstRect.w = m_Transform->m_Width * m_Transform->m_Scale;
		m_DstRect.h = m_Transform->m_Height * m_Transform->m_Scale;
	}

	void Draw() override
	{
		if (m_drawCollider)
		{
			TextureManager::Draw(m_Texture, m_SrcRect, m_DstRect, SDL_FLIP_NONE);
		}
	}

};
