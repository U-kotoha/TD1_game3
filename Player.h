#pragma once
#include <Struct.h>
#include <Bullet.h>

//�v���C���[�̃N���X
class Player {
public:

	int player_hp;

	Transform player_;
	Bullet* P_Bullet;

public:

	//�R���X�g���N�^
	Player();
	//�f�X�g���N�^
	~Player();

	//�����o�֐�
	void Move(Bullet* P_Bullet, char* keys);
	void Draw(Bullet* P_Bullet);
};