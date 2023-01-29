#pragma once
#include <Struct.h>
#include <EnemyBullet.h>

class Enemy {
public:

	//メンバ変数
	int enemy_hp;
	Transform enemy_;
	EnemyBullet* E_Bullet;

public:

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