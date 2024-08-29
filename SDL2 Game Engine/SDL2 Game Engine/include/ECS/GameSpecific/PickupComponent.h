#pragma once
#include <string>
#include "../EntityComponentSystem.h"
#include "../SpriteComponent.h"

class PickupComponent : public Component
{
public:
    PickupComponent(std::string p_TextureID) : m_Value(10), m_Tag(p_TextureID) 
	{
		m_SpriteComponent = nullptr;
	}
    ~PickupComponent() = default;

	void Init() override
	{
		if (m_Tag == "coin")
		{
			m_SpriteComponent = &m_Entity->GetComponent<SpriteComponent>();

			m_SpriteComponent->m_Animations.emplace("Idle", Animation(0, 8, 100));
			m_SpriteComponent->Play("Idle");
		}
	}

    int GetValue() const { return m_Value; }

private:
    int m_Value;
	std::string m_Tag;
	SpriteComponent* m_SpriteComponent;
};
