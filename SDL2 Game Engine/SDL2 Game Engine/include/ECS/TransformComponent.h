#pragma once
#include "EntityComponentSystem.h"
#include "../Vector2D.h"

class TransformComponent : public Component
{
public:
    Vector2D m_Position;

    int m_Width = 32;
    int m_Height = 32;
    int m_Scale = 1;

    TransformComponent()
    {
        m_Position.Zero();
    }

    TransformComponent(int p_Scale)
    {
        m_Position.Zero();
        m_Scale = p_Scale;
    }

    TransformComponent(float p_X, float p_Y)
    {
        m_Position.m_X = p_X;
        m_Position.m_Y = p_Y;
    }

    TransformComponent(float p_X, float p_Y, int p_W, int p_H, int p_Scale)
    {
        m_Position.m_X = p_X;
        m_Position.m_Y = p_Y;
        m_Width = p_W;
        m_Height = p_H;
        m_Scale = p_Scale;
    }
};