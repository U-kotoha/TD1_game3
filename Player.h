#pragma once
#include <Struct.h>
#include <Bullet.h>

class Player {
public:

	Player(int x, int y, int radius, int speed);

	Player_ player_;
	Bullet* P_Bullet;

public:
	//コンストラクタ
	Player();
	//デストラクタ
	~Player();

	void Move(Bullet* P_Bullet, char* keys);
	void Draw(Bullet* P_Bullet);

};