#pragma once
#include <map>
#include <string>
#include <SDL.h>
#include "EntityComponentSystem.h"
#include "../Animation.h"
#include "../Game.h"
#include "../AssetManager.h"
#include "../TextureManager.h"

class TransformComponent;
struct SDL_Texture;

class SpriteComponent : public Component
{
private:
    TransformComponent* m_Transform = nullptr;
    SDL_Texture* m_Texture = nullptr;
    SDL_Rect m_SrcRect{}, m_DstRect{};

    bool m_Animated = false;
    int m_Frames = 0;
    int m_Speed = 100;

public:
    int m_AnimIndex = 0;
    std::map<std::string, Animation> m_Animations;
    SDL_RendererFlip m_SpriteFlip = SDL_FLIP_NONE;

    SpriteComponent() = default;

    explicit SpriteComponent(const std::string& p_TextureID)
    {
        SetTexture(p_TextureID);
    }

    SpriteComponent(const std::string& p_TextureID, bool p_IsAnimated)
        : m_Animated(p_IsAnimated)
    {
        SetTexture(p_TextureID);
    }

    ~SpriteComponent() override
    {
        
    }

    void SetTexture(const std::string& p_TextureID)
    {
        m_Texture = Game::s_Assets->GetTexture(p_TextureID);
    }

    void Init() override
    {
        m_Transform = &m_Entity->GetComponent<TransformComponent>();
        m_SrcRect = {0, 0, m_Transform->m_Width, m_Transform->m_Height};
    }

    void Update() override
    {
        // If the sprite is animated, update the source rectangle's x position based on the current frame
        if (m_Animated)
        {
            m_SrcRect.x = m_SrcRect.w * static_cast<int>((SDL_GetTicks() / m_Speed) % m_Frames);
        }

        // Update the source rectangle's y position based on the animation index
        m_SrcRect.y = m_AnimIndex * m_Transform->m_Height;

        // Update the destination rectangle's position and size for rendering
        m_DstRect = {
            static_cast<int>(m_Transform->m_Position.m_X),
            static_cast<int>(m_Transform->m_Position.m_Y),
            m_Transform->m_Width * m_Transform->m_Scale,
            m_Transform->m_Height * m_Transform->m_Scale
        };
    }

    void Draw() override
    {
        TextureManager::Draw(m_Texture, m_SrcRect, m_DstRect, m_SpriteFlip);
    }

    void Play(const std::string& p_AnimName)
    {
        const auto& anim = m_Animations[p_AnimName];
        m_Frames = anim.m_Frames;
        m_AnimIndex = anim.m_Index;
        m_Speed = anim.m_Speed;
    }
};
