#include "Body.h"

Body::Body(int xPos, int yPos)
{
	x = xPos;
	y = yPos;
}

Body::Body(int xPos, int yPos, int direction, bool head)
{
	x = xPos;
	y = yPos;
	isHead = head;
	switch (direction)
	{
	case 0:
		currentDirection = Body::Direction::UP;
		break;
	case 1:
		currentDirection = Body::Direction::DOWN;
		break;
	case 2:
		currentDirection = Body::Direction::LEFT;
		break;
	case 3:
		currentDirection = Body::Direction::RIGHT;
		break;
	default:
		break;
	}
}

int Body::GetX()
{
	return x;
}

int Body::GetY()
{
	return y;
}

void Body::FeedCheck()
{
	if (gameManager.frame[y][x] == 3)
	{
		gameManager.DecreaseFeedCount();

		if (isHead)
		{
			gameManager.AddScore(50);
			isEatFeed = true;
		}
	}
}

void Body::Move()
{
	gameManager.frame[y][x] = 0;
	switch (currentDirection)
	{
	case Direction::UP:
		--y;
		break;
	case Direction::DOWN:
		++y;
		break;
	case Direction::LEFT:
		--x;
		break;
	case Direction::RIGHT:
		++x;
		break;
	default:
		break;
	}

	FeedCheck();
	GameOverCheck();
}

void Body::GameOverCheck()
{
	if (isHead && (gameManager.frame[y][x] == 1))
	{
		gameManager.GameOver();
	}
}

void Body::SetDirection(int direction)
{
	switch (direction)
	{
	case 0:
		currentDirection = Direction::UP;
		break;
	case 1:
		currentDirection = Direction::LEFT;
		break;
	case 2:
		currentDirection = Direction::RIGHT;
		break;
	case 3:
		currentDirection = Direction::DOWN;
		break;
	default:
		break;
	}
}

void Body::SetDirection(Direction direction)
{
	currentDirection = direction;
}

Body::Direction Body::GetDirection()
{
	return currentDirection;
}

bool Body::GetIsHead()
{
	return isHead;
}

bool Body::GetIsEatFeed()
{
	return isEatFeed;
}

void Body::InitIsEatFeed()
{
	isEatFeed = false;
}