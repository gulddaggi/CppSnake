#include <iostream>
#include <vector>
#include <Windows.h>
#include <conio.h>
#include <random>


const int LEN_X = 21; // 가로
const int LEN_Y = 15; // 세로

#define LEFTARROW 75
#define RIGHTARROW 77
#define UPARROW 72
#define DOWNARROW 80

int feedCount = 0;
bool isGameOver = false;
int totalScore = 0;

std::vector<std::vector<int>> frame; // 접근 : frame[y][x]

// 뱀 몸체
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

public:
	Body(int xPos, int yPos)
	{
		x = xPos;
		y = yPos;
	}

	Body(int xPos, int yPos, int direction, bool head)
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

	void FeedCheck()
	{
		if (frame[y][x] == 3)
		{
			--feedCount;
			if (isHead)
			{
				totalScore += 50;
				isEatFeed = true;
			}
		}
	}

	void GameOverCheck()
	{
		if (isHead && (frame[y][x] == 1))
		{
			isGameOver = true;
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

	bool GetIsHead()
	{
		return isHead;
	}

	bool GetIsEatFeed()
	{
		return isEatFeed;
	}

	void InitIsEatFeed()
	{
		isEatFeed = false;
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
		++feedCount;
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
	bool isEatFeed = true;

	Direction currentHeadDirection;
	Body::Direction newBodyDirection;

public:
	Snake(int xPos, int yPos, int count) 
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
			frame[bodyVector[i].GetY()][bodyVector[i].GetX()] = 2;
		}

		headX = bodyVector[0].GetX();
		headY = bodyVector[0].GetY();
		GameOverCheck();
	}

	void GameOverCheck()
	{
		if (frame[headY][headX] == 1)
		{
			isGameOver = true;
		}

		for (int i = 1; i < bodyVector.size(); i++)
		{
			if (headY == bodyVector[i].GetY() && headX == bodyVector[i].GetX())
			{
				isGameOver = true;
				break;
			}
		}
	}

	void AddBody()
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
		bodyVector[bodyVector.size() - 1].SetDirection(newBodyDirection);
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

	bool GetIsEatFeed()
	{
		return isEatFeed;
	}

	void InitIsEatFeed()
	{
		isEatFeed = false;
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
	std::cout << "Score : " << totalScore << '\n';
	std::cout << "Feed : " << feedCount << '\n';
}

int main()
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> xRandom(1, LEN_X-3);
	std::uniform_int_distribution<int> yRandom(1, LEN_Y-3);

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


	system("cls");
	DrawGame(LEN_X, LEN_Y);

	while (true)
	{
		// 먹이
		if (snake.GetIsEatFeed() || feedCount == 0)
		{
			snake.InitIsEatFeed();
			while (true)
			{
				int x = xRandom(gen);
				int y = yRandom(gen);
				if (frame[y][x] == 0)
				{
					Feed feed(xRandom(gen), yRandom(gen));
					frame[feed.GetY()][feed.GetX()] = 3;
					break;
				}
			}
		}

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
		snake.Move();
		DrawGame(LEN_X, LEN_Y);
		if (isGameOver)
		{
			std::cout << "\t\t\t\t   GAME OVER" << '\n';
			Sleep(1000);
			break;
		}
		Sleep(100);
	}

	return 0;
}