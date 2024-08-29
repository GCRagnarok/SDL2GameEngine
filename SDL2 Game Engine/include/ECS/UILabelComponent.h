#pragma once
#include <string> 
#include <SDL.h> 
#include <SDL_ttf.h>
#include "../AssetManager.h"

// Forward declarations
class Component;
class Game;
class AbstractGame;

class UILabelComponent : public Component
{
public:
    UILabelComponent(int p_XPos, int p_YPos, const std::string p_Text, const std::string p_Font, SDL_Color& p_Colour) :
        m_LabelText(p_Text), m_LabelFont(p_Font), m_TextColour(p_Colour)
    {
        m_Position.x = p_XPos;
        m_Position.y = p_YPos;

        SetLabelText(m_LabelText, m_LabelFont);
    }

    ~UILabelComponent()
    {
        SDL_DestroyTexture(m_LabelTexture);
    }

    // Render the text to a surface, create a texture from it, and update the label's dimensions
    void SetLabelText(const std::string p_Text, const std::string p_Font)
    {
        SDL_Surface* surf = TTF_RenderText_Blended(Game::s_Assets->GetFont(p_Font), p_Text.c_str(), m_TextColour);
        m_LabelTexture = SDL_CreateTextureFromSurface(AbstractGame::s_Renderer, surf);
        SDL_FreeSurface(surf);

        SDL_QueryTexture(m_LabelTexture, nullptr, nullptr, &m_Position.w, &m_Position.h);
    }

    void Draw() override
    {
        SDL_RenderCopy(Game::s_Renderer, this->m_LabelTexture, nullptr, &this->m_Position);
    }

private:
    SDL_Rect m_Position;
    const std::string m_LabelText;
    const std::string m_LabelFont;
    SDL_Color m_TextColour;
    SDL_Texture* m_LabelTexture = nullptr;
};
