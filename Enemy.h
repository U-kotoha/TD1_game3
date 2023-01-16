#pragma once
#include <Struct.h>
#include <EnemyBullet.h>

class Enemy {
public:

	int enemy_hp;
	
	Transform enemy_;
	EnemyBullet* E_Bullet;

	//コンストラクタ
	Enemy();

	//デストラクタ
	~Enemy();

	//メンバ関数
	void Update();
	void Draw();

	//弾が当たった時の処理
	void OnCollision();
};