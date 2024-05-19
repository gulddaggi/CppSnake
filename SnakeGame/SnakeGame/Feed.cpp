#include "Feed.h"

Feed::Feed(int xPos, int yPos)
{
	x = xPos;
	y = yPos;
}

int Feed::GetX()
{
	return x;
}

int Feed::GetY()
{
	return y;
}

void Feed::EatBySnake()
{
	delete this;
}

void Feed::SetX(int value)
{
	x = value;
}

void Feed::SetY(int value)
{
	y = value;
}