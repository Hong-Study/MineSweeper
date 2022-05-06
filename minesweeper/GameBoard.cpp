#include "GameBoard.h"
#include "Consts.h"
#include <iostream>
#include <string>
GameBoard::GameBoard(int Boom_count, int Map_size)
	: Boom_count(Boom_count)
	, Map_size(Map_size)
{
	x = 1;
	y = 1;
	ScreenInit();
	Create_Map();
	Show_Map();
}

GameBoard::~GameBoard()
{
	std::cout << "GameOver! Bro" << std::endl;
	ScreenRelease();
}

void GameBoard::Create_Map()
{
	for (int i = 0; i < Map_size; ++i) {
		std::vector<Tile> a(Map_size);
		Maps.push_back(a);
		for (int j = 0; j < Map_size; ++j) {
			if (i == 0 || j == 0 || i == (Map_size - 1) || j == (Map_size - 1)) {
				Maps[i][j].Type = Map::BORDER;
				Maps[i][j].Visible = true;
			}
			else {
				Maps[i][j].Type = Map::NOTBOMB;
				Maps[i][j].Visible = false;
			}
			Maps[i][j].came = false;
		}
	}
	std::random_device rd;
	// random_device 를 통해 난수 생성 엔진을 초기화 한다.
	std::mt19937 gen(rd());
	// 0 부터 99 까지 균등하게 나타나는 난수열을 생성하기 위해 균등 분포 정의.
	std::uniform_int_distribution<int> dis(1, Map_size-1);

	for (int i = 0; i < Boom_count;) {
		int x = dis(gen);
		int y = dis(gen);
		if (Maps[y][x].Type == Map::NOTBOMB) {
			Maps[y][x].Type = Map::BOMB;
			++i;
		}
	}
	for (int i = 1; i < Map_size-1; ++i) {
		for (int j = 1; j < Map_size-1; ++j) {
			if (Maps[i][j].Type == Map::BOMB) {
				Maps[i - 1][j+1].count++;
				Maps[i - 1][j].count++;
				Maps[i - 1][j-1].count++;
				Maps[i + 1][j + 1].count++;
				Maps[i + 1][j].count++;
				Maps[i + 1][j - 1].count++;
				Maps[i][j-1].count++;
				Maps[i][j+1].count++;
			}
		}
	}
}

void GameBoard::Show_Map()
{
	/*for (int i = 0; i < Map_size; ++i) {
		for (int j = 0; j < Map_size; ++j) {
			if (Maps[i][j].Type == Map::NOTBOMB) {
				if (Maps[i][j].count == 0)
					std::cout << Maps[i][j].count << " ";
				else
					std::cout << Maps[i][j].count << " ";
			}
			else if (Maps[i][j].Type == Map::BOMB)
				std::cout << "◎";
			else
				std::cout << "ㅁ";
		}
		std::cout << std::endl;
	}*/
	Render();
	if (Boom_count == 0) {
		std::cout << "승리하셨습니다!" << std::endl;
		exit(0);
	}
}

void GameBoard::RecursiveBackTraing(int in_y, int in_x) {
	int r, nx, ny;
	Maps[in_y][in_x].came = true;
	for (r = 0; r < 8; r++) {
		nx = in_x + DIR[r][0];
		ny = in_y + DIR[r][1];
		if (Maps[ny][nx].Type == Map::NOTBOMB) {
			if (Maps[ny][nx].count != 0) {
				Maps[ny][nx].Visible = true;
			}
			else if (inRange(ny, nx) && !Maps[ny][nx].came && Maps[ny][nx].count == 0) {
				RecursiveBackTraing(ny, nx);
				//std::cout << ny << " : " << nx << std::endl;
				Maps[ny][nx].Visible = true;
			}
		}
	}
}

bool GameBoard::inRange(int y, int x)
{
	return (y > 0 && y < Map_size - 1) && (x > 0 && x < Map_size - 1);
}
void GameBoard::Check(int y, int x) {
	for (int i = y - 1; i <= y + 1; ++i) {
		for (int j = x - 1; j <= x + 1; ++j) {
			if (Maps[i][j].Type == Map::NOTBOMB) {
				Maps[i][j].Visible = true;
				if (Maps[i][j].count == 0)
					RecursiveBackTraing(i, j);
			}
		}
	}
}
void GameBoard::Flag() {
	if (Maps[y][x].Type == Map::BOMB) {
		Maps[y][x].Type = Map::FLAG;
		Maps[y][x].Visible = true;
		Boom_count--;
	}
}
void GameBoard::Move_Right()
{
	x++;
	if (x > Map_size - 2)
		x = Map_size - 2;
}

void GameBoard::Move_Left()
{
	--x;
	if (x < 1)
		x = 1;
}

void GameBoard::Move_Up()
{
	--y;
	if (y < 1)
		y = 1;
}

void GameBoard::Move_Down()
{
	++y;
	if (y > Map_size - 2)
		y = Map_size - 2;
}
void GameBoard::Click() {
	if (Maps[y][x].Type == Map::BOMB) {
		std::cout << "GameOver! Bro" << std::endl;
		exit(0);
	}
	else if (Maps[y][x].Type == Map::NOTBOMB) {
		Check(y, x);
	}
}
void GameBoard::ScreenInit()
{
	CONSOLE_CURSOR_INFO cci;

	//화면 버퍼 2개를 만든다.
	g_hScreen[0] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);
	g_hScreen[1] = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

	//커서를 숨긴다.
	cci.dwSize = 1;
	cci.bVisible = FALSE;
	SetConsoleCursorInfo(g_hScreen[0], &cci);
	SetConsoleCursorInfo(g_hScreen[1], &cci);
}

void GameBoard::ScreenFlipping()
{
	SetConsoleActiveScreenBuffer(g_hScreen[g_nScreenIndex]);
	g_nScreenIndex = !g_nScreenIndex;
}

void GameBoard::ScreenClear()
{
	for (int i = 0; i < Map_size; i++) {
		COORD Coor = { i, 0 };
		DWORD dw;
		FillConsoleOutputCharacter(g_hScreen[g_nScreenIndex], ' ', 80 * 25, Coor, &dw);
	}
}

void GameBoard::ScreenRelease()
{
	CloseHandle(g_hScreen[0]);
	CloseHandle(g_hScreen[1]);
}

void GameBoard::ScreenPrint(int x, int y, std::string s)
{
	DWORD dw;
	COORD CursorPosition = { x, y };
	SetConsoleCursorPosition(g_hScreen[g_nScreenIndex], CursorPosition);
	WriteFile(g_hScreen[g_nScreenIndex], s.c_str(), s.size(), &dw, NULL);
}

void GameBoard::Render()
{
	ScreenClear();
	std::string s;
	for (int i = 0; i < Map_size; ++i) {
		for (int j = 0; j < Map_size; ++j) {
			if (i == y && j == x)
				s += "☆";
			else if (Maps[i][j].Visible) {
				if (Maps[i][j].Type == Map::NOTBOMB) {
					if (Maps[i][j].count == 0)
						s += " ";
					else
						s += std::to_string(Maps[i][j].count);
						s += " ";
				}
				else if (Maps[i][j].Type == Map::FLAG)
					s += "◎";
				else
					s += "ㅁ";
			}
			else {
				s += "■";
			}
		}
		s += "\n";
	}
	ScreenPrint(0, 0, s);
	ScreenFlipping();
}