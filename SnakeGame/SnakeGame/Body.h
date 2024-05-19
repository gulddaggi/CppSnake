#pragma once
#include "GameManager.h"

class Body
{
public:
	enum class Direction
	{
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

private:
	int x;
	int y;
	bool isHead = false;
	bool isEatFeed = false;

	Direction currentDirection;
	GameManager& gameManager = GameManager::getInstance();

public:
	Body(int xPos, int yPos);
	Body(int xPos, int yPos, int direction, bool head);

	int GetX();
	int GetY();

	void Move();

	void FeedCheck();

	void GameOverCheck();

	void SetDirection(int direction);

	void SetDirection(Direction direction);

	Direction GetDirection();

	bool GetIsHead();

	bool GetIsEatFeed();

	void InitIsEatFeed();

};

