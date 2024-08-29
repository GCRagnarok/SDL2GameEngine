#pragma once
#include <SDL.h>
#include <SDL_image.h>

class TextureManager {

public:
	static SDL_Texture* LoadTexture(const char* p_FileName);
	static void Draw(SDL_Texture* p_Texture, SDL_Rect p_SrcRect, SDL_Rect p_DstRect, SDL_RendererFlip p_Flip);

};

