#pragma once
#include "EntityComponentSystem.h"
#include "../Physics.h"
#include "../Vector2D.h"

class Rigidbody2DComponent : public Component
{
private:
    Physics& m_Physics;
    float m_GravityScale = 1.0f;
    bool m_IsGrounded = false;

public:
    Vector2D m_Velocity;
    Rigidbody2DComponent(Physics& p_Physics) : m_Velocity(0.0f, 0.0f), m_Physics(p_Physics) {}

    void Update() override
    {
        if (!m_IsGrounded)
        {
            m_Velocity = m_Physics.ApplyGravity(m_Velocity, m_GravityScale);
        }
    }

    Vector2D GetVelocity() const
    {
        return m_Velocity;
    }

    void SetVelocity(const Vector2D& velocity)
    {
        m_Velocity = velocity;
    }

    void SetGrounded(bool isGrounded)
    {
        m_IsGrounded = isGrounded;
        if (isGrounded)
        {
            m_Velocity.m_Y = 0;
        }
    }

    bool IsGrounded() const
    {
        return m_IsGrounded;
    }

    float GetGravity() const
    {
        return m_Physics.GetGravity();
    }

    float GetDeltaTime() const
    {
        return m_Physics.GetDeltaTime();
    }
};
