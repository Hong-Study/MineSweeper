#pragma once
#include<vector>
#include<random>

class GameBoard
{
private:
	struct Tile {
		int Type;
		int count;
		bool Visible;
		bool came;
	};
	enum Direction {
		LEFT,
		RIGHT,
		UP,
		DOWN,
	};
	const int DIR[8][2] = { {0,-1},{0,+1},{-1,0},{+1,0},{1,1},{1,-1},{-1,-1},{-1,1} }; 
	int x, y;
	std::vector<std::vector<Tile>> Maps;
	int Map_size;
	int Boom_count;
public:
	GameBoard(int Boom_count, int Map_size);
	~GameBoard();
	void Create_Map();
	void Show_Map();
	void Move_Right();
	void Move_Left();
	void Move_Up();
	void Move_Down();
	void Click();
	void RecursiveBackTraing(int y, int x);
	bool inRange(int y, int x);
	void Check(int y, int x);
	void Flag();
};

