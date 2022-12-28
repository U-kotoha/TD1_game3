#pragma once
#include <Struct.h>
#include <Bullet.h>

class Player {
public:

	Player_ player_;
	Bullet* P_Bullet;

public:
	//�R���X�g���N�^
	Player(int x, int y, int radius, int speed);
	//�f�X�g���N�^
	~Player();

	void Move(Bullet* P_Bullet, char* keys);
	void Draw(Bullet* P_Bullet);

};