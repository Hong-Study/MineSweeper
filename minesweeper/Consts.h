#pragma once   

namespace Key {
	const int UP = 72;
	const int DOWN = 80;
	const int LEFT = 75;
	const int RIGHT = 77;
	const int F = 102;
	const int SPACEBAR = 32;
};

namespace Map {
	const int NOTBOMB = 0;
	const int BOMB = 1;
	const int BORDER = 2;
	const int FLAG = 3;

	const int EASY_SIZE = 11;
	const int NORMAL_SIZE = 16;
	const int HARD_SIZE = 21;

	const int EASY_BOMB_COUNT = 10;
	const int NORMAL_BOMB_COUNT = 25;
	const int HARD_BOMB_COUNT = 55;

	const int EASY_MODE = 1;
	const int NORMAL_MODE = 2;
	const int HARD_MODE = 3;
}