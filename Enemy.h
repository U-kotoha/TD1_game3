#pragma once
#include <Struct.h>
#include <EnemyBullet.h>

class Enemy {
public:

	int enemy_hp;
	
	Transform enemy_;
	EnemyBullet* E_Bullet;

	//�R���X�g���N�^
	Enemy();

	//�f�X�g���N�^
	~Enemy();

	//�����o�֐�
	void Update();
	void Draw();

	//�e�������������̏���
	void OnCollision();
};