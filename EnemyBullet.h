#pragma once
#include <Struct.h>

//�G�̒e�̃N���X
class EnemyBullet {
public:

	//�����o�ϐ�
	bool enemy_isShot;
	Transform enemybullet_;

	//�R���X�g���N�^
	EnemyBullet();

	//�����o�֐�
	void Draw();

};