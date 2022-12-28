#pragma once
#include <Struct.h>

class Player {
public:

	Player(int x, int y, int radius, int speed);

	Player_ player_;

	void Move(char* keys);
	void Draw();

};