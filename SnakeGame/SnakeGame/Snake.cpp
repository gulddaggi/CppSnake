#include "Snake.h"

Snake::Snake(int xPos, int yPos, int count)
{
	headX = xPos;
	headY = yPos;
	bodyCount = count;
	currentHeadDirection = Direction::RIGHT;

	Body body(xPos, yPos, (int)currentHeadDirection, true);
	bodyVector.push_back(body);

	for (int i = 1; i < count; i++)
	{
		Body body(xPos - i, yPos, (int)currentHeadDirection, false);
		bodyVector.push_back(body);
	}
}

int Snake::GetHeadX()
{
	return headX;
}

int Snake::GetHeadY()
{
	return headY;
}

int Snake::GetBodyCount()
{
	return bodyCount;
}

Snake::Direction Snake::GetHeadDirction()
{
	return currentHeadDirection;
}

std::vector<Body>& Snake::GetBody()
{
	return bodyVector;
}

void Snake::Move()
{
	for (int i = bodyVector.size() - 1; i > 0; i--)
	{
		if (i == bodyVector.size() - 1)
			newBodyDirection = bodyVector[i].GetDirection();

		bodyVector[i].Move();
		bodyVector[i].SetDirection(bodyVector[i - 1].GetDirection());
	}
	bodyVector[0].Move();

	if (bodyVector[0].GetIsEatFeed())
	{
		AddBody();
		isEatFeed = true;
		bodyVector[0].InitIsEatFeed();
	}

	for (int i = 0; i < bodyVector.size(); i++)
	{
		gameManager.frame[bodyVector[i].GetY()][bodyVector[i].GetX()] = 2;
	}

	headX = bodyVector[0].GetX();
	headY = bodyVector[0].GetY();
	GameOverCheck();
}

void Snake::GameOverCheck()
{
	if (gameManager.frame[headY][headX] == 1)
	{
		gameManager.GameOver();
	}

	for (int i = 1; i < bodyVector.size(); i++)
	{
		if (headY == bodyVector[i].GetY() && headX == bodyVector[i].GetX())
		{
			gameManager.GameOver();
			break;
		}
	}
}

void Snake::AddBody()
{
	Body& tail = bodyVector[bodyVector.size() - 1];
	int x, y;

	switch (newBodyDirection)
	{
		case Body::Direction::UP:
			x = tail.GetX();
			y = tail.GetY() + 1;
			break;

		case Body::Direction::DOWN:
			x = tail.GetX();
			y = tail.GetY() - 1;
			break;

		case Body::Direction::LEFT:
			x = tail.GetX() + 1;
			y = tail.GetY();
			break;

		case Body::Direction::RIGHT:
			x = tail.GetX() - 1;
			y = tail.GetY();
			break;

		default:
			break;
	}

	Body body(x, y, 0, false);
	bodyVector.push_back(body);
	bodyVector[bodyVector.size()-1].SetDirection(newBodyDirection);
}

void Snake::SetHeadDirection(int direction)
{
	switch (direction)
	{
	case 0:
		bodyVector[0].SetDirection(0);
		break;
	case 1:
		bodyVector[0].SetDirection(1);
		break;
	case 2:
		bodyVector[0].SetDirection(2);
		break;
	case 3:
		bodyVector[0].SetDirection(3);
		break;
	default:
		break;
	}
}

bool Snake::GetIsEatFeed()
{
	return isEatFeed;
}

void Snake::InitIsEatFeed()
{
	isEatFeed = false;
}