#include "../include/Collision.h"
#include "../include/ECS/ColliderComponent.h"
#include "../include/ECS/Rigidbody2DComponent.h"
#include "../include/ECS/GameSpecific/PlayerComponent.h"
#include "../include/AbstractGame.h"

// Check if two rectangles are overlapping
bool Collision::AABB(SDL_Rect& p_RectA, SDL_Rect& p_RectB)
{
    return (
        p_RectA.x + p_RectA.w >= p_RectB.x &&
        p_RectB.x + p_RectB.w >= p_RectA.x &&
        p_RectA.y + p_RectA.h >= p_RectB.y &&
        p_RectB.y + p_RectB.h >= p_RectA.y
        );
}

// Check if two rectangles are overlapping and adjust position to resolve collision
bool Collision::AABB(SDL_Rect& p_RectA, SDL_Rect& p_RectB, Vector2D& p_PositionA)
{
    if (
        p_RectA.x + p_RectA.w >= p_RectB.x &&
        p_RectB.x + p_RectB.w >= p_RectA.x &&
        p_RectA.y + p_RectA.h >= p_RectB.y &&
        p_RectB.y + p_RectB.h >= p_RectA.y
        )
    {
        // Calculate the overlap on both axes
        int overlapX = (p_RectA.x + p_RectA.w / 2) - (p_RectB.x + p_RectB.w / 2);
        int overlapY = (p_RectA.y + p_RectA.h / 2) - (p_RectB.y + p_RectB.h / 2);

        // Determine the direction of the collision
        if (std::abs(overlapX) > std::abs(overlapY))
        {
            // Horizontal collision
            if (overlapX > 0)
            {
                p_PositionA.m_X = static_cast<float>(p_RectB.x + p_RectB.w);
            }
            else
            {
                p_PositionA.m_X = static_cast<float>(p_RectB.x - p_RectA.w);
            }
        }
        else
        {
            // Vertical collision
            if (overlapY > 0)
            {
                p_PositionA.m_Y = static_cast<float>(p_RectB.y + p_RectB.h);
            }
            else
            {
                p_PositionA.m_Y = static_cast<float>(p_RectB.y - p_RectA.h);
            }
        }

        return true;
    }

    return false;
}

// Check if two colliders are overlapping and adjust position to resolve collision if necessary
bool Collision::AABB(ColliderComponent& p_ColliderA, ColliderComponent& p_ColliderB)
{
    Vector2D positionA = p_ColliderA.m_Entity->GetComponent<TransformComponent>().m_Position;

    if (
        p_ColliderA.m_Collider.x + p_ColliderA.m_Collider.w >= p_ColliderB.m_Collider.x &&
        p_ColliderB.m_Collider.x + p_ColliderB.m_Collider.w >= p_ColliderA.m_Collider.x &&
        p_ColliderA.m_Collider.y + p_ColliderA.m_Collider.h >= p_ColliderB.m_Collider.y &&
        p_ColliderB.m_Collider.y + p_ColliderB.m_Collider.h >= p_ColliderA.m_Collider.y
        )
    {
        // Calculate the overlap on both axes
        int overlapX = (p_ColliderA.m_Collider.x + p_ColliderA.m_Collider.w / 2) - (p_ColliderB.m_Collider.x + p_ColliderB.m_Collider.w / 2);
        int overlapY = (p_ColliderA.m_Collider.y + p_ColliderA.m_Collider.h / 2) - (p_ColliderB.m_Collider.y + p_ColliderB.m_Collider.h / 2);

        // Calculate the overlap width and height
        int overlapWidth = std::min(p_ColliderA.m_Collider.x + p_ColliderA.m_Collider.w, p_ColliderB.m_Collider.x + p_ColliderB.m_Collider.w) - std::max(p_ColliderA.m_Collider.x, p_ColliderB.m_Collider.x);
        int overlapHeight = std::min(p_ColliderA.m_Collider.y + p_ColliderA.m_Collider.h, p_ColliderB.m_Collider.y + p_ColliderB.m_Collider.h) - std::max(p_ColliderA.m_Collider.y, p_ColliderB.m_Collider.y);

        // Determine the direction of the collision
        if (std::abs(overlapY) > std::abs(overlapX))
        {
            // Vertical collision
            if (overlapY > 0)
            {
                positionA.m_Y = static_cast<float>(p_ColliderB.m_Collider.y + p_ColliderB.m_Collider.h);
            }
            else
            {
                positionA.m_Y = static_cast<float>(p_ColliderB.m_Collider.y - p_ColliderA.m_Collider.h);
            }
        }
        else
        {
            // Horizontal collision
            if (overlapX > 0)
            {
                positionA.m_X = static_cast<float>(p_ColliderB.m_Collider.x + p_ColliderB.m_Collider.w);
            }
            else
            {
                positionA.m_X = static_cast<float>(p_ColliderB.m_Collider.x - p_ColliderA.m_Collider.w);
            }
        }

        p_ColliderA.m_Entity->GetComponent<TransformComponent>().m_Position = positionA;
        return true;
    }

    return false;
}

// Determine the direction of the collision between two colliders
Collision::Direction Collision::GetCollisionDirection(ColliderComponent& p_ColliderA, ColliderComponent& p_ColliderB)
{
    if (AABB(p_ColliderA.m_Collider, p_ColliderB.m_Collider))
    {
        // Calculate the overlap on both axes
        int overlapX = (p_ColliderA.m_Collider.x + p_ColliderA.m_Collider.w / 2) - (p_ColliderB.m_Collider.x + p_ColliderB.m_Collider.w / 2);
        int overlapY = (p_ColliderA.m_Collider.y + p_ColliderA.m_Collider.h / 2) - (p_ColliderB.m_Collider.y + p_ColliderB.m_Collider.h / 2);

        // Calculate the overlap width and height
        int overlapWidth = std::min(p_ColliderA.m_Collider.x + p_ColliderA.m_Collider.w, p_ColliderB.m_Collider.x + p_ColliderB.m_Collider.w) - std::max(p_ColliderA.m_Collider.x, p_ColliderB.m_Collider.x);
        int overlapHeight = std::min(p_ColliderA.m_Collider.y + p_ColliderA.m_Collider.h, p_ColliderB.m_Collider.y + p_ColliderB.m_Collider.h) - std::max(p_ColliderA.m_Collider.y, p_ColliderB.m_Collider.y);

        // Define the minimum overlap percentage
        const float minOverlapPercentage = 0.1f; // 10%

        // Calculate the current overlap percentages
        float overlapPercentageX = static_cast<float>(overlapWidth) / p_ColliderA.m_Collider.w;
        float overlapPercentageY = static_cast<float>(overlapHeight) / p_ColliderA.m_Collider.h;

        // Determine the direction of the collision
        if (std::abs(overlapY) > std::abs(overlapX))
        {
            // Vertical collision
            if (overlapY > 0)
            {
                // Bottom collision with percentage check
                if (overlapPercentageX >= minOverlapPercentage)
                {
                    return Direction::Bottom;
                }
            }
            else
            {
                // Top collision with percentage check
                if (overlapPercentageX >= minOverlapPercentage)
                {
                    return Direction::Top;
                }
            }
        }
        else
        {
            // Horizontal collision
            if (overlapX > 0)
            {
                // Right collision with percentage check
                if (overlapPercentageY >= minOverlapPercentage)
                {
                    return Direction::Right;
                }
            }
            else
            {
                // Left collision with percentage check
                if (overlapPercentageY >= minOverlapPercentage)
                {
                    return Direction::Left;
                }
            }
        }
    }

    return Direction::None;
}

// Limit the collider's position to the defined bounds
void Collision::LimitToBounds(SDL_Rect& p_Rect, int p_Width, int p_Height)
{

    if (p_Rect.x < 0)
    {
        p_Rect.x = 0;
    }
    else if (p_Rect.x + p_Rect.w > p_Width)
    {
        p_Rect.x = p_Width - p_Rect.w;
    }

    if (p_Rect.y < 0)
    {
        p_Rect.y = 0;
    }
    else if (p_Rect.y + p_Rect.h > p_Height)
    {
        p_Rect.y = p_Height - p_Rect.h;
    }
}

// Limit the collider's position to the defined bounds
void Collision::LimitToBounds(ColliderComponent& p_Collider, int p_Width, int p_Height)
{
    Vector2D& position = p_Collider.m_Entity->GetComponent<TransformComponent>().m_Position;

    int colliderWidth = p_Collider.m_Collider.w;
    int colliderHeight = p_Collider.m_Collider.h;

    if (position.m_X < 0)
    {
        position.m_X = 0;
    }
    else if (position.m_X + colliderWidth > p_Width)
    {
        position.m_X = static_cast<float>(p_Width - colliderWidth);
    }

    if (position.m_Y < 0)
    {
        position.m_Y = 0;
    }
    else if (position.m_Y + colliderHeight > p_Height)
    {
        position.m_Y = static_cast<float>(p_Height - colliderHeight);
    }
}

// Limit the collider's position to the defined width
void Collision::LimitToWidth(SDL_Rect& p_Rect, int p_Width)
{

    if (p_Rect.x < 0)
    {
        p_Rect.x = 0;
    }
    else if (p_Rect.x + p_Rect.w > p_Width)
    {
        p_Rect.x = p_Width - p_Rect.w;
    }
}

// Limit the collider's position to the defined width
void Collision::LimitToWidth(ColliderComponent& p_Collider, int p_Width)
{
    Vector2D& position = p_Collider.m_Entity->GetComponent<TransformComponent>().m_Position;

    int colliderWidth = p_Collider.m_Collider.w;
    int colliderHeight = p_Collider.m_Collider.h;

    if (position.m_X < 0)
    {
        position.m_X = 0;
    }
    else if (position.m_X + colliderWidth > p_Width)
    {
        position.m_X = static_cast<float>(p_Width - colliderWidth);
    }
}