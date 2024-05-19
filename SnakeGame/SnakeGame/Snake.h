#pragma once
#include <vector>
#include "Body.h"

class Snake
{
public:
	enum class Direction
	{
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	std::vector<Body> bodyVector;

private:
	int headX;
	int headY;
	int bodyCount;
	bool isEatFeed = true;
	GameManager& gameManager = GameManager::getInstance();

	Direction currentHeadDirection;
	Body::Direction newBodyDirection;

public:
	Snake(int xPos, int yPos, int count);

	int GetHeadX();

	int GetHeadY();

	int GetBodyCount();

	Direction GetHeadDirction();

	std::vector<Body>& GetBody();

	void Move();

	void GameOverCheck();

	void AddBody();

	void SetHeadDirection(int direction);

	bool GetIsEatFeed();

	void InitIsEatFeed();
};

