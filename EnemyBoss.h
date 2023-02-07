#pragma once
#include <Struct.h>
#include <EnemyBullet.h>

//敵ボスのクラス
class EnemyBoss {
public:

	//メンバ変数
	int enemyboss_hp;
	Transform enemyboss_;
	EnemyBullet* E_Bullet;

public:

	//コンストラクタ
	EnemyBoss();

	//デストラクタ
	~EnemyBoss();

	//メンバ関数
	void Update();
	void Draw();

	//弾が当たった時の処理
	void OnCollision();
};