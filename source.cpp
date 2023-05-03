#include <iostream>
#include <ctime>	// to create different random numbers
#include <curses.h>

using namespace std;

//-----------Properties----------//
const int Snake_Max = 10;
enum Direction { Top = 1, Down, Right, Left };
struct Map { int Width, Height, FruitX, FruitY; };
struct Snake { int HeadX, HeadY, Tail_N, Tail_X[Snake_Max+1], Tail_Y[Snake_Max+1]; Direction Dir; };
struct Player { int Score; bool Lose; string msg; };
//-------------------------------//
Map Map1; Snake Snake1; Player Player1;

void Shift_Right(int arr[], int size)	{
	for (int i = size ; i >= 0; i--)
		arr[i+1] = arr[i];
}

int Max_rand(int r)	{
	srand(time(NULL));
	return rand() % (r -2) + 1;	// 1-->(r-2)
}

void Generate_fruit()	{	
	Map1.FruitX = Max_rand(Map1.Width);		//	1 - 38
	Map1.FruitY = Max_rand(Map1.Height);	//	1 - 38
}

void Setup()	{
	Map1.Width = 40;
	Map1.Height = 20;
	Generate_fruit();
	//---------
	Snake1.HeadX = Map1.Width / 2;
	Snake1.HeadY = Map1.Height / 2;
	Snake1.Tail_N = 0;
	// Snake1.Dir = Top;
	//---------
	Player1.Score = 0;
	Player1.Lose = false;
	Player1.msg = "You lose :/";
}

void Check_lose()	{
	if (Snake1.Tail_N == Snake_Max)	{
		Player1.Lose = true;
		Player1.msg = "You Win :)";
	}
	for (int i = 0; i < Snake1.Tail_N; i++)	{
		if (Snake1.HeadX == Snake1.Tail_X[i] && Snake1.HeadY == Snake1.Tail_Y[i])
			Player1.Lose = true;
	}
	if (Snake1.HeadY >= Map1.Height || Snake1.HeadY <= 0 ||
	Snake1.HeadX >= Map1.Width || Snake1.HeadX <= 0)
		Player1.Lose = true;
}

void Draw()	{
	system("clear");
	for	(int i = 0; i < Map1.Height; i++)	{
		for	(int j = 0; j < Map1.Width; j++)	{
			if (i == 0 || i == Map1.Height -1)					cout << "*";
			else if (j == 0 || j == Map1.Width -1)				cout << "*";
			else if (i == Snake1.HeadY && j == Snake1.HeadX)	cout << "O";
			else if (i == Map1.FruitY && j == Map1.FruitX)		cout << "$";
			else if (Snake1.Tail_N){
				bool printed = false;
				for (int z = 0; z < Snake1.Tail_N; z++)
				{
					if (Snake1.Tail_X[z] == j && Snake1.Tail_Y[z] == i)
					{
						cout << "o";
						printed = true;
						break;
					}
				}
				if (!printed) cout << " ";
			}
			else cout << " ";
		}
		cout << endl;
	}
	cout << "Player Score : " << Player1.Score << endl;
	cout << "Max Score : " << Snake_Max << endl;

	if (Player1.Lose)
	{
		cout << Player1.msg << endl;
		exit(0);
	}
	
}

void Input()	{	
	initscr();
	cbreak();
	noecho();
	scrollok(stdscr, TRUE);
	nodelay(stdscr, TRUE); // Do not wait for a char
	char c = getch();
	switch (c) {
		case 'w': Snake1.Dir = Top; break;
		case 's': Snake1.Dir = Down;	break;
		case 'd': Snake1.Dir = Right;	break;
		case 'a': Snake1.Dir = Left;	break;
		case 'x': Player1.Lose = true;
	}
  	endwin();
}


void Move() {

	if (Snake1.Tail_N)
	{
			Shift_Right(Snake1.Tail_X, Snake1.Tail_N);
			Shift_Right(Snake1.Tail_Y, Snake1.Tail_N);
			Snake1.Tail_X[0] = Snake1.HeadX;
			Snake1.Tail_Y[0] = Snake1.HeadY;
	}
	
	switch (Snake1.Dir)
	{
		case Top:	Snake1.HeadY--;	break;
		case Down:	Snake1.HeadY++;	break;
		case Right:	Snake1.HeadX++;	break;
		case Left:	Snake1.HeadX--;	break;
	}

	if (Snake1.HeadX == Map1.FruitX && Snake1.HeadY == Map1.FruitY)
	{
		Generate_fruit();
		Player1.Score++;
		Snake1.Tail_N++;
	}
}

void Test_Draw()	{
	Setup();
	for (int i = 0; i < 5; i++){
		Draw();
		Move();
	}
}

void Test_Move() {
	Setup();
	for (int i = 0; i < 7; i++){
		int c = Max_rand(6);
		switch (c) {
			case '1': Snake1.Dir = Top;
			case '2': Snake1.Dir = Down;
			case '3': Snake1.Dir = Right;
			case '4': Snake1.Dir = Left;
		}
		Draw();
		Move();
	}
}

void Test_Input()	{
	for (int i = 0; i < 10; i++)	{
		cout << endl << (10-i) << " Seconds left"<< endl;
		Input();
		cout << "Snake Direction is:" << Snake1.Dir << endl;
		//sleep(1);
		napms(500);
	}
}

int main()	{
	Setup();
	while (!Player1.Lose)
	{
		Check_lose();
		Draw();
		Input();
		Move();
		napms(150);
	}
	return 0;
}
