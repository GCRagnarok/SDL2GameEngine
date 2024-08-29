#include <iostream>
#include "../../../include/ECS/GameSpecific/PlayerComponent.h"
#include "../../../include/Animation.h"
#include "../../../include/Physics.h"
#include "../../../include/ECS/EntityComponentSystem.h"
#include "../../../include/ECS/GameSpecific/PickupComponent.h"
#include "../../../include/ECS/AudioComponent.h"
#include "../../../include/ECS/ColliderComponent.h"


PlayerComponent::PlayerComponent(Manager& p_Manager, UILabelComponent* p_ScoreLabel)
	: m_Manager(p_Manager), m_ScoreLabel(p_ScoreLabel), m_SpaceKeyHeld(false)
{
    
}

PlayerComponent::~PlayerComponent()
{
}

void PlayerComponent::Init()
{
    m_TransformComponent = &m_Entity->GetComponent<TransformComponent>();
    m_SpriteComponent = &m_Entity->GetComponent<SpriteComponent>();
    m_SpriteComponent->m_Animations.emplace("Idle", Animation(0, 2, 200));
    m_SpriteComponent->m_Animations.emplace("Walk", Animation(1, 4, 100));
    m_SpriteComponent->m_Animations.emplace("Jump", Animation(2, 1, 100));
    m_SpriteComponent->m_Animations.emplace("Fall", Animation(3, 1, 100));
    m_SpriteComponent->Play("Idle");
    m_ScoreComponent = &m_Entity->GetComponent<ScoreComponent>();
    m_RB2DComponent = &m_Entity->GetComponent<Rigidbody2DComponent>();
}

void PlayerComponent::Update()
{
    Collisions(*m_Entity, m_Manager);
    HandleInput();
    Fall();
    Movement();
	UpdateAnimationState();
}

// Input Actions
void PlayerComponent::Movement()
{
    // Update position based on velocity
    m_TransformComponent->m_Position.m_X += m_RB2DComponent->GetVelocity().m_X * m_Speed;
    m_TransformComponent->m_Position.m_Y += m_RB2DComponent->GetVelocity().m_Y;
}

void PlayerComponent::Jump()
{
    if (m_RB2DComponent->IsGrounded())
    {
        m_RB2DComponent->m_Velocity.m_Y = -static_cast<float>(m_JumpForce);
        m_RB2DComponent->SetGrounded(false); // Reset grounded state after jumping
    }
}

// Adjust the player's vertical velocity based on whether they are falling or performing a low jump
void PlayerComponent::Fall()
{
    if (m_RB2DComponent->m_Velocity.m_Y > 0)
    {
        m_RB2DComponent->m_Velocity.m_Y += m_RB2DComponent->GetGravity() * (m_FallMultiplier - 1) * m_RB2DComponent->GetDeltaTime();

    }
    else if (m_RB2DComponent->m_Velocity.m_Y < 0 && !SDL_GetKeyboardState(NULL)[SDL_SCANCODE_SPACE]) // Jumping but space is released
    {
        m_RB2DComponent->m_Velocity.m_Y += m_RB2DComponent->GetGravity() * (m_LowJumpMultiplier - 1) * m_RB2DComponent->GetDeltaTime();
    }
}

void PlayerComponent::HandleInput()
{
    if (m_RB2DComponent == nullptr || m_SpriteComponent == nullptr) {
        std::cerr << "Error: m_TransformComponent or m_SpriteComponent is nullptr" << std::endl;
        return;
    }

    const Uint8* keystate = SDL_GetKeyboardState(NULL);

    if (AbstractGame::s_Event.type == SDL_KEYDOWN || AbstractGame::s_Event.type == SDL_KEYUP)
    {
        if (keystate[SDL_SCANCODE_A] || keystate[SDL_SCANCODE_LEFT])
        {
            m_RB2DComponent->m_Velocity.m_X = -1;
            m_SpriteComponent->m_SpriteFlip = SDL_FLIP_HORIZONTAL;
			m_flip = true;
        }
        else if (keystate[SDL_SCANCODE_D] || keystate[SDL_SCANCODE_RIGHT])
        {
            m_RB2DComponent->m_Velocity.m_X = 1;
            m_SpriteComponent->m_SpriteFlip = SDL_FLIP_NONE;
            m_flip = false;
        }
        else
        {
            m_RB2DComponent->m_Velocity.m_X = 0;
        }

        if (keystate[SDL_SCANCODE_SPACE] && !m_SpaceKeyHeld)
        {
            Jump();
            m_SpaceKeyHeld = true; 
        }
        else if (!keystate[SDL_SCANCODE_SPACE])
        {
            m_SpaceKeyHeld = false; 
        }

        if (keystate[SDL_SCANCODE_ESCAPE])
        {
            AbstractGame::s_IsRunnning = false;
        }
    }
}

// Score
void PlayerComponent::AddScore(int points)
{
    if (m_ScoreComponent)
    {
        m_ScoreComponent->AddScore(points);
    }
}

int PlayerComponent::GetScore() const
{
    return m_ScoreComponent ? m_ScoreComponent->GetScore() : 0;
}

// Collisions
void PlayerComponent::Collisions(Entity& p_Player, Manager& p_Manager)
{
    // Screen Bounds
    Collision::LimitToWidth(p_Player.GetComponent<ColliderComponent>(), AbstractGame::s_WindowWidth);

    // Block Colliders
    auto& blockColliders = m_Manager.GetGroup(AssetManager::groupColliders);
    bool isGrounded = false;

    for (auto& c : blockColliders)
    {
        // Check for any collision
        if (Collision::AABB(p_Player.GetComponent<ColliderComponent>(), c->GetComponent<ColliderComponent>()))
        {
            // Check the collision direction
            Collision::Direction direction = Collision::GetCollisionDirection(p_Player.GetComponent<ColliderComponent>(), c->GetComponent<ColliderComponent>());
            if (direction == Collision::Direction::Top)
            {
                isGrounded = true;
                m_BottomCollision = false;
                break;
            }
            else if (direction == Collision::Direction::Bottom && !m_BottomCollision)
            {
                // Cancel the jump by setting vertical velocity to zero
                m_RB2DComponent->m_Velocity.m_Y = 0;
                m_BottomCollision = true;
            }
        }
    }
    p_Player.GetComponent<Rigidbody2DComponent>().SetGrounded(isGrounded);


    // Pickups
    auto& pickupColliders = m_Manager.GetGroup(AssetManager::groupPickups);
    for (auto& p : pickupColliders)
    {
        if (Collision::AABB(p_Player.GetComponent<ColliderComponent>(), p->GetComponent<ColliderComponent>()))
        {
            int pickupValue = p->GetComponent<PickupComponent>().GetValue();
            AddScore(pickupValue);
            p->GetComponent<AudioComponent>().PlaySound(Game::s_Assets->GetSound("pickup_sound"), -1, 0);
            p->Destroy();
        }
    }
}

// Animations
void PlayerComponent::UpdateAnimationState()
{
    PlayerState currentState = DeterminePlayerState();

    switch (currentState)
    {
    case PlayerComponent::PlayerState::Idle:
        if (m_flip)
        {
            m_SpriteComponent->m_SpriteFlip = SDL_FLIP_HORIZONTAL;
        }
        else
        {
            m_SpriteComponent->m_SpriteFlip = SDL_FLIP_NONE;
        }
        m_SpriteComponent->Play("Idle");
        break;

    case PlayerComponent::PlayerState::Walk:
        m_SpriteComponent->Play("Walk");
        break;

    case PlayerComponent::PlayerState::Jump:
        m_SpriteComponent->Play("Jump");
        break;

    case PlayerComponent::PlayerState::Fall:
        m_SpriteComponent->Play("Fall");
        break;

    default:
        break;
    }
}

PlayerComponent::PlayerState PlayerComponent::DeterminePlayerState()
{
    if (m_RB2DComponent->GetVelocity().m_Y < 0)
    {
        return PlayerState::Jump;
    }
    else if (m_RB2DComponent->GetVelocity().m_Y > 0)
    {
        return PlayerState::Fall;
    }
    else if (m_RB2DComponent->GetVelocity().m_X != 0)
    {
        return PlayerState::Walk;
    }
    else
    {
        return PlayerState::Idle;
    }
}
