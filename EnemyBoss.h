#pragma once
#include <Struct.h>
#include <EnemyBullet.h>

//�G�{�X�̃N���X
class EnemyBoss {
public:

	//�����o�ϐ�
	int enemyboss_hp;
	Transform enemyboss_;
	EnemyBullet* E_Bullet;

public:

	//�R���X�g���N�^
	EnemyBoss();

	//�f�X�g���N�^
	~EnemyBoss();

	//�����o�֐�
	void Update();
	void Draw();

	//�e�������������̏���
	void OnCollision();
};