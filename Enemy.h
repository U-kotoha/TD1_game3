#pragma once
#include <Struct.h>

class Enemy {
public:

	Enemy_ enemy_;

	//�R���X�g���N�^
	Enemy();

	//�����o�֐�
	void Update();
	void Draw();

	//�e�������������̏���
	void OnCollision();
};