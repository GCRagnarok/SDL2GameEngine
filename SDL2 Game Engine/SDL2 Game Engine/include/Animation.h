#pragma once

struct Animation
{
	int m_Index = 0;
	int m_Frames = 0;
	int m_Speed = 0;

	Animation() = default;

	Animation(int p_Index, int p_Frames, int p_Speed)
		: m_Index(p_Index), m_Frames(p_Frames), m_Speed(p_Speed)
	{

	}
};
