#pragma once
#include "Vector2D.h"

class Physics
{
private:
    float m_Gravity = 9.81f;
    float m_DeltaTime = 60.0f / 1000.0f;

public:

    Physics(){}

    void SetDeltaTime(float deltaTime)
    {
        m_DeltaTime = deltaTime;
    }

	float GetDeltaTime() const
	{
		return m_DeltaTime;
	}

    float GetGravity() const
    {
        return m_Gravity;
    }

    Vector2D ApplyGravity(const Vector2D& p_Velocity, float p_GravityScale)
    {
        Vector2D newVelocity = p_Velocity;
        newVelocity.m_Y += m_Gravity * p_GravityScale * m_DeltaTime;
        return newVelocity;
    }
};