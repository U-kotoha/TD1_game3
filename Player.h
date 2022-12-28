#pragma once
#include <Struct.h>
#include <Bullet.h>

class Player {
public:

	Player_ player_;
	Bullet* P_Bullet;

public:
	//コンストラクタ
	Player(int x, int y, int radius, int speed);
	//デストラクタ
	~Player();

	void Move(Bullet* P_Bullet, char* keys);
	void Draw(Bullet* P_Bullet);

};