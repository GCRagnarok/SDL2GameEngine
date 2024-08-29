#pragma once
#include <SDL.h>
#include "Vector2D.h"

class ColliderComponent;

class Collision
{
public:

	enum class Direction { None, Top, Bottom, Left, Right };

	static bool AABB(SDL_Rect& p_RectA, SDL_Rect& p_RectB);
	static bool AABB(SDL_Rect& p_RectA, SDL_Rect& p_RectB, Vector2D& p_PositionA);
	static bool AABB(ColliderComponent& p_ColliderA, ColliderComponent& p_ColliderB);
	static Direction GetCollisionDirection(ColliderComponent& p_ColliderA, ColliderComponent& p_ColliderB);
	static void LimitToBounds(SDL_Rect& p_Rect, int p_ScreenWidth, int p_ScreenHeight);
	static void LimitToBounds(ColliderComponent& p_Collider, int p_ScreenWidth, int p_ScreenHeight);
	static void LimitToWidth(SDL_Rect& p_Rect, int p_ScreenWidth);
	static void LimitToWidth(ColliderComponent& p_Collider, int p_ScreenWidth);
};
