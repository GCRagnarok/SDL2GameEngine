#pragma once
#include "AbstractGame.h"

class Entity;
class UILabelComponent;	
class GameStateManager;

class Game : public AbstractGame
{
public:
	Game();
	~Game();

	void LoadGame();

	Entity* GetPlayer() const { return m_Player; }

private:
	void Update();
	void Render();

	Entity* m_Player;
	UILabelComponent* m_ScoreLabel;
	GameStateManager* m_GameStateManager;

};
