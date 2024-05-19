#pragma once
#include "GameManager.h"

class Feed
{
private:
	int x;
	int y;
	GameManager& gameManager = GameManager::getInstance();

public:
	Feed(int xPos, int yPos);

	int GetX();
	void SetX(int value);

	int GetY();
	void SetY(int value);

	void EatBySnake();
};

