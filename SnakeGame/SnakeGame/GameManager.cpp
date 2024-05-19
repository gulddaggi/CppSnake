#include "GameManager.h"
#include "Snake.h"
#include "Feed.h"

GameManager& GameManager::getInstance() {
	static GameManager s;
	return s;
}

int GameManager::GetLENX() const
{
	return LEN_X;
}

int GameManager::GetLENY() const
{
	return LEN_Y;
}

void GameManager::InitStage(Snake& snake, Feed& feed)
{
	// 초기화
	for (int i = 0; i < LEN_Y; i++)
	{
		std::vector<int> row(LEN_X, 0);
		frame.push_back(row);
	}

	// 채울 좌표 지정
	// 테두리
	for (int i = 0; i < LEN_Y; i++)
	{
		for (int j = 0; j < LEN_X; j++)
		{
			if (i == 0 || j == 0 || j == LEN_X - 1 || i == LEN_Y - 1) frame[i][j] = 1;
			else frame[i][j] = 0;
		}
	}

	// 뱀
	for (auto body : snake.GetBody())
	{
		frame[body.GetY()][body.GetX()] = 2;
	}

	// 먹이
	FeedCheck(snake, feed);
}

bool GameManager::GetIsGameOver() const
{
	return isGameOver;
}

void GameManager::GameOver()
{
	isGameOver = true;
}

void GameManager::DecreaseFeedCount()
{
	--feedCount;
}

int GameManager::GetFeedCount()
{
	return feedCount;
}

void GameManager::AddScore(int value)
{
	totalScore += value;
}

void GameManager::AddFeedCount()
{
	++feedCount;
}

void GameManager::FeedCheck(Snake& snake, Feed& feed)
{
	if (snake.GetIsEatFeed() || feedCount == 0)
	{
		CreateFeed(snake, feed);
	}
}

void GameManager::CreateFeed(Snake& snake, Feed& feed)
{
	snake.InitIsEatFeed();

	while (true)
	{
		feedX = xRandom(generator);
		feedY = yRandom(generator);

		if (frame[feedY][feedX] != 1 && frame[feedY][feedX] != 2)
		{
			feed.SetX(feedX);
			feed.SetY(feedY);
			frame[feedY][feedX] = 3;
			AddFeedCount();
			return;
		}
	}
}

int GameManager::GetTotalScore()
{
	return totalScore;
}
