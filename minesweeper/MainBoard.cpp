#include "MainBoard.h"
#include <iostream>
#include <conio.h>

using namespace std;

MainBoard::MainBoard()
{	
	cout << "\t << M E N U >> \t" << endl; cout << endl;
	cout << "\t 1. 초급 모드 ( 10 × 10 )\t" << endl; cout << endl;
	cout << "\t 2. 중급 모드 ( 15 × 15 )\t" << endl; cout << endl;
	cout << "\t 3. 고급 모드 ( 20 × 20 )\t" << endl; cout << endl;
	cout << "\t 4. 종료 하기\t" << endl; cout << endl;
	cout << "\t 메뉴를 입력하세요 : ";
	cin >> menu;

	switch (menu) {
	case Map::EASY_MODE:
		system("cls");
		board = new GameBoard(Map::EASY_BOMB_COUNT, Map::EASY_SIZE);
		break;
	case Map::NORMAL_MODE:
		system("cls");
		board = new GameBoard(Map::NORMAL_BOMB_COUNT, Map::NORMAL_SIZE);
		break;
	case Map::HARD_MODE:
		system("cls");
		board = new GameBoard(Map::HARD_BOMB_COUNT, Map::HARD_SIZE);
		break;
	case 4:
		return;
	}
	Start();

}

void MainBoard::Start()
{
	int input = 0;
	while (1) {
		if (_kbhit()) {
			input = _getch();
			switch (input) {
			case Key::DOWN:
				board->Move_Down();
				break;
			case Key::UP:
				board->Move_Up();
				break;
			case Key::LEFT:
				board->Move_Left();
				break;
			case Key::RIGHT:
				board->Move_Right();
				break;
			case Key::SPACEBAR:
				board->Click();
				break;
			case Key::F:
				board->Flag();
			}
			system("cls");
			//std::cout << input;
			board->Show_Map();
		}
	}
}
