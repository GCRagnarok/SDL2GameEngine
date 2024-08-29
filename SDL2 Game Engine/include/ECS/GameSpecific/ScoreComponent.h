#pragma once
#include "../EntityComponentSystem.h"
#include "../UILabelComponent.h"

class ScoreComponent : public Component
{
public:
    ScoreComponent(UILabelComponent* scoreLabel)
        : m_ScoreLabel(scoreLabel), m_Score(0) {}

	void Init() override
	{
        m_ScoreLabel->SetLabelText("SCORE: " + std::to_string(m_Score), "pixel");
	}

    void AddScore(int amount)
    {
        m_Score += amount;
        UpdateScoreLabel();
    }

    int GetScore() const
    {
        return m_Score;
    }

private:

    void UpdateScoreLabel()
    {
        m_ScoreLabel->SetLabelText("SCORE: " + std::to_string(m_Score), "pixel");
    }

    UILabelComponent* m_ScoreLabel;
    int m_Score;
};
