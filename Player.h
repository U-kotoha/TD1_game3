#pragma once
#include <Struct.h>
#include <Bullet.h>

//�v���C���[�̃N���X
class Player {
public:

	Player_ player_;
	Bullet* P_Bullet;

public:

	//�R���X�g���N�^
	Player(int x, int y, int radius, int speed);
	//�f�X�g���N�^
	~Player();

	//�����o�֐�
	void Move(Bullet* P_Bullet, char* keys);
	void Draw(Bullet* P_Bullet);
};