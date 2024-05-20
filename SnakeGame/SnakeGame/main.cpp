#include <iostream>
#include <vector>
#include <Windows.h>
#include <conio.h>
#include "GameManager.h"
#include "Snake.h"
#include "Feed.h"

#define LEFTARROW 75
#define RIGHTARROW 77
#define UPARROW 72
#define DOWNARROW 80

void DrawGame(int x, int y, std::vector<std::vector<int>>& frame)
{
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			if (frame[i][j] == 1) std::cout << "▦";
			else if (frame[i][j] == 2) std::cout << "■";
			else if (frame[i][j] == 3) std::cout << "◆";
			else std::cout << "  ";
		}
		std::cout << '\n';
	}
}

int main()
{
	system("mode con:cols=100 lines=40 | title Title");
	GameManager& gameManager = GameManager::getInstance();
	std::vector<std::vector<int>>& gameFrame = gameManager.frame;

	// 마우스 커서 숨기기
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

	int lenY = gameManager.GetLENY();
	int lenX = gameManager.GetLENX();

	// 뱀
	Snake snake(10, 10, 5);
	Feed feed(0, 0);

	gameManager.InitStage(snake, feed);
	system("cls");
	DrawGame(lenX, lenY, gameFrame);

	while (true)
	{
		// 먹이
		gameManager.FeedCheck(snake, feed);

		int inputKey;
		if (_kbhit())
		{
			inputKey = _getch();
			if (inputKey == 224)
			{
				inputKey = _getch();
				switch (inputKey)
				{
					case UPARROW:
						snake.SetHeadDirection(0);
						break;
					case LEFTARROW:
						snake.SetHeadDirection(1);
						break;
					case RIGHTARROW:
						snake.SetHeadDirection(2);
						break;
					case DOWNARROW:
						snake.SetHeadDirection(3);
						break;
					default:
						break;
				}
			}
		}

		if (gameManager.GetIsGameOver())
		{
			std::cout << "\t\t   GAME OVER" << '\n';
			Sleep(1000);

			std::string word;
			std::cout << "Retry? (y/n) : ";
			std::cin >> word;
			if (word == "y")
			{
				gameManager.ReStart(snake, feed);
				system("cls");
			}
			else
			{
				break;
			}
		}

		COORD pos = { 0, 0 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
		snake.Move();
		DrawGame(lenX, lenY, gameFrame);
		std::cout << "Score : " << gameManager.GetTotalScore() << '\n';
		
		Sleep(100);
	}

	return 0;
}