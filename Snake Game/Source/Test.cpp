#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

bool GameOver;

const int width = 25;
const int height = 25;

int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int nTail = 0;

enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;


void Setup()
{
	GameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
}



void Draw()
{
	system("cls");
	for (int i = 0; i < width+2; i++) 
	{
		cout << "#";
	}
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
			{
				cout << "#";
			}
			
			if (i == y && j == x)
			{
				cout << "O";
			}
			else if(i == fruitY && j == fruitX)
			{
				cout << "F";
			}
			else {
				int print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (j == tailX[k] && i == tailY[k])
					{
						cout << "o";
						print = true;
					}
				}
				if (!print)
				{
				cout << " ";
				}
			}

			if (j == width - 1)
			{
				cout << "#";
			}
		}
		cout << endl;
	}

	for (int i = 0; i < height+2; i++)
	{
		cout << "#";
	}
	cout << endl;
	cout << "Score: " << score << endl;
}



void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			break;
		case 'd':
			dir = RIGHT;
			break;
		case 'w':
			dir = UP;
			break;
		case 's':
			dir = DOWN;
			break;
		case 'x':
			GameOver = true;
		}
	}
}



void Logic()
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;

	for (int i = 1; i < nTail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (dir)
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	default:
		break;
	}
	
	// if (x > width || x < 0 || y > height || y < 0)
	//{
		//GameOver = true;
	//}

	if (x >= width)
	{
		x = 0;
	}
	else if (x < 0)
	{
		x = width - 1;
	}

	if (y >= height)
	{
		y = 0;
	}
	else if (y < 0)
	{
		y = height - 1;
	}

	for (int i = 0; i < nTail; ++i)
	{
		if (x == tailX[i] && y == tailY[i])
		{
			GameOver = true;
		}
	}

	if (x == fruitX && y == fruitY)
	{
		nTail += 1;
		score += 1;
		fruitX = rand() % width;
		fruitY = rand() % height;
	}
}



int main()
{
	Setup();
	while (!GameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep(15);
	}

	return 0;
}