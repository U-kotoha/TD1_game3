#pragma once
#include <Struct.h>

class Enemy {
public:

	Enemy_ enemy_;

	Enemy();

	void Update();
	void Draw();

	void OnCollision();
	//当たった時の処理
};