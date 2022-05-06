#pragma once
#include <vector>
#include "Consts.h"
#include "GameBoard.h"

class MainBoard
{
private:
	int menu;
	GameBoard* board;
public:
	MainBoard();
	void Start();
};

