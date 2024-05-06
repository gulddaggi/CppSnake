#include <iostream>
#include <vector>
#include <Windows.h>
#include <conio.h>
#include <random>


const int LEN_X = 41; // 가로
const int LEN_Y = 30; // 세로

#define LEFTARROW 75
#define RIGHTARROW 77
#define UPARROW 72
#define DOWNARROW 80

std::vector<std::vector<int>> frame; // 접근 : frame[y][x]

class Feed
{
private:
	int x;
	int y;

public:
	Feed(int xPos, int yPos)
	{
		x = xPos;
		y = yPos;
	}

	int GetX()
	{
		return x;
	}

	int GetY()
	{
		return y;
	}

	void EatBySnake()
	{
		delete this;
	}
};

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

private:
	int headX;
	int headY;
	int bodyCount;

	Direction currentHeadDirection;

public:
	Snake(int xPos, int yPos, int count) 
	{
		headX = xPos;
		headY = yPos;
		bodyCount = count;
		currentHeadDirection = Direction::RIGHT;
	}

	int GetHeadX()
	{
		return headX;
	}

	int GetHeadY()
	{
		return headY;
	}
	
	int GetBodyCount() 
	{
		return bodyCount;
	}

	Direction GetHeadDirction()
	{
		return currentHeadDirection;
	}

};

void DrawGame(int x, int y)
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
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> xRandom(1, 39);
	std::uniform_int_distribution<int> yRandom(1, 28);

	system("mode con:cols=100 lines=40 | title Title");

	// 마우스 커서 숨기기
	CONSOLE_CURSOR_INFO cursorInfo = { 0, };
	cursorInfo.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);

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
			if (i == 0 || j == 0 || j == LEN_X - 1 || i == LEN_Y-1) frame[i][j] = 1;
			else frame[i][j] = 0;
		}
	}

	// 뱀
	Snake snake(10, 10, 5);
	for (int i = 0; i < snake.GetBodyCount(); i++)
	{
		frame[snake.GetHeadY()][snake.GetHeadX()-i] = 2;
	}

	// 먹이
	Feed feed(xRandom(gen), yRandom(gen));
	frame[feed.GetY()][feed.GetX()] = 3;

	system("cls");
	DrawGame(LEN_X, LEN_Y);


}