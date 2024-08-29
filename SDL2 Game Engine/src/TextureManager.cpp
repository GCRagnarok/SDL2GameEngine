#include "../include/TextureManager.h"
#include "../include/Game.h"

SDL_Texture* TextureManager::LoadTexture(const char* p_Asset)
{
	SDL_Surface* tempSurface = IMG_Load(p_Asset);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(Game::s_Renderer, tempSurface);
	SDL_FreeSurface(tempSurface);

	return texture;
}

void TextureManager::Draw(SDL_Texture* p_Texture, SDL_Rect p_SrcRect, SDL_Rect p_DstRect, SDL_RendererFlip p_Flip)
{
	SDL_RenderCopyEx(Game::s_Renderer, p_Texture, &p_SrcRect, &p_DstRect, NULL, NULL, p_Flip);
}