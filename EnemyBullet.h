#pragma once
#include <Struct.h>

//敵の弾のクラス
class EnemyBullet {
public:

	bool enemy_isShot;
	Transform enemybullet_;

	//コンストラクタ
	EnemyBullet();

	//メンバ関数
	void Draw();

};