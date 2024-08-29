#pragma once
#include <string>
#include "../EntityComponentSystem.h"
#include "../../Collision.h"
#include "../../Vector2D.h"
#include "../TransformComponent.h"
#include "../SpriteComponent.h"
#include "ScoreComponent.h"
#include "../UILabelComponent.h"
#include "../Rigidbody2DComponent.h"

class PlayerComponent : public Component
{
public:
    PlayerComponent(Manager& p_Manager, UILabelComponent* p_ScoreLabel);
    ~PlayerComponent();

    void Init() override;
    void Update() override;

    void HandleInput();
	void Movement();
    void Jump();
	void Fall();
    void AddScore(int points);
    int GetScore() const;
    void Collisions(Entity& p_Player, Manager& p_Manager);

private:
	enum class PlayerState
	{
		Idle,
		Walk,
		Jump,
		Fall
	};
    PlayerState DeterminePlayerState();
    void UpdateAnimationState();

    Vector2D m_Position;
    Vector2D m_Velocity;
	float m_Speed = 3.0f;
    int m_Score = 0;
    int m_JumpForce = 7;
    float m_FallMultiplier = 2.5f;
    float m_LowJumpMultiplier = 5.0f;
    bool m_SpaceKeyHeld;
    bool m_BottomCollision = false;
	bool m_flip = false;
    const char* m_CurrentState = "Idle";

    Manager& m_Manager;
    TransformComponent* m_TransformComponent = nullptr;
    SpriteComponent* m_SpriteComponent = nullptr;
    Rigidbody2DComponent* m_RB2DComponent = nullptr;
    ScoreComponent* m_ScoreComponent = nullptr;
    UILabelComponent* m_ScoreLabel = nullptr;
	ColliderComponent* m_ColliderComponent = nullptr;
};
