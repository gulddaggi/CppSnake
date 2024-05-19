#ifndef G_H
#define G_H

#pragma once
#include <vector>
#include <iostream>
#include <random>

#pragma once
class GameManager
{
private:
	GameManager() {}
	GameManager(const GameManager& ref) {}
	GameManager& operator=(const GameManager& ref) {}
	~GameManager() {}

	const int LEN_X = 21; // 가로
	const int LEN_Y = 15; // 세로

	std::default_random_engine generator;
	std::uniform_int_distribution<int> xRandom{ 1, LEN_X-1 };
	std::uniform_int_distribution<int> yRandom{ 1, LEN_Y-1 };

	bool isGameOver = false;

	int totalScore = 0;

	int feedCount = 0;
	int feedX = 0;
	int feedY = 0;

public:
	std::vector<std::vector<int>> frame; // 접근 : frame[y][x]

	static GameManager& getInstance();

	int GetLENX() const;
	int GetLENY() const;

	int GetFeedCount();
	void DecreaseFeedCount();
	void AddFeedCount();

	void AddScore(int value);

	void InitStage(class Snake& snake, class Feed& feed);

	void GameOver();
	bool GetIsGameOver() const;

	void FeedCheck(Snake& snake, Feed& feed);
	void CreateFeed(Snake& snake, Feed& feed);

	int GetTotalScore();
};

#endif 

