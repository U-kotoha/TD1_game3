#pragma once
#include <Struct.h>

//敵の弾のクラス
class EnemyBullet {
public:

	//メンバ変数
	bool enemy_isShot;
	Transform enemybullet_;

	//コンストラクタ
	EnemyBullet();

	//メンバ関数
	void Draw();

};