#pragma once
#include <Struct.h>

class Enemy {
public:

	Enemy_ enemy_;

	//コンストラクタ
	Enemy();

	//メンバ関数
	void Update();
	void Draw();

	//弾が当たった時の処理
	void OnCollision();
};