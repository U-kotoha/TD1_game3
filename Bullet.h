#pragma once
#include <Struct.h>

//�e�̃N���X
class Bullet {
public:

	int bulletMax;
	int bulletCount;
	Bullet_ bullet_[10];

public:

	//�R���X�g���N�^
	Bullet();

	//�����o�֐�
	void Update(char* keys);
	void Draw();
};