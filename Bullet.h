#pragma once
#include <Struct.h>

//�v���C���[�̒e�̃N���X
class Bullet {
public:

	int bulletMax;
	int bulletCount;
	bool isShot[10];
	Transform bullet_[10];

public:

	//�R���X�g���N�^
	Bullet();

	//�����o�֐�
	void Update(char* keys);
	void Draw();
};