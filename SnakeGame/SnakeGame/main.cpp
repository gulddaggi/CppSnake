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

// 뱀 몸체
class Body
{
private:
	int x;
	int y;

	enum class Direction
	{
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	Direction currentDirection;
public:
	Body(int xPos, int yPos)
	{
		x = xPos;
		y = yPos;
	}

	Body(int xPos, int yPos, int direction)
	{
		x = xPos;
		y = yPos;
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

	int GetX()
	{
		return x;
	}

	int GetY()
	{
		return y;
	}

	void Move()
	{
		frame[y][x] = 0;
		switch (currentDirection)
		{
			case Direction::UP:
				if (y - 1 != 0)
				{
					--y;
				}
				break;
			case Direction::DOWN:
				if (y + 1 != LEN_Y-1)
				{
					++y;
				}
				break;
			case Direction::LEFT:
				if (x-1 != 0)
				{
					--x;
				}
				break;
			case Direction::RIGHT:
				if (x + 1 != LEN_X-1)
				{
					++x;
				}
				break;
			default:
				break;
		}
	}

	void SetDirection(int direction)
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

	void SetDirection(Direction direction)
	{
		currentDirection = direction;
	}

	Direction GetDirection()
	{
		return currentDirection;
	}
};

// 먹이
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

// 뱀
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

	Direction currentHeadDirection;

public:
	Snake(int xPos, int yPos, int count) 
	{
		headX = xPos;
		headY = yPos;
		bodyCount = count;
		currentHeadDirection = Direction::RIGHT;

		for (int i = 0; i < count; i++)
		{
			Body body(xPos - i, yPos, (int)currentHeadDirection);
			bodyVector.push_back(body);
		}
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

	std::vector<Body>& GetBody()
	{
		return bodyVector;
	}

	void Move()
	{
		for (int i = bodyVector.size()-1; i > 0; i--)
		{
			bodyVector[i].Move();
			bodyVector[i].SetDirection(bodyVector[i - 1].GetDirection());
		}
		bodyVector[0].Move();

		for (int i = 0; i < bodyVector.size(); i++)
		{
			frame[bodyVector[i].GetY()][bodyVector[i].GetX()] = 2;
		}
	}

	void SetHeadDirection(int direction)
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
	for(auto body : snake.GetBody())
	{
		frame[body.GetY()][body.GetX()] = 2;
	}

	// 먹이
	Feed feed(xRandom(gen), yRandom(gen));
	frame[feed.GetY()][feed.GetX()] = 3;

	system("cls");
	DrawGame(LEN_X, LEN_Y);

	while (true)
	{
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

		COORD pos = { 0, 0 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
		DrawGame(LEN_X, LEN_Y);
		snake.Move();
		Sleep(100);
	}

	return 0;
}