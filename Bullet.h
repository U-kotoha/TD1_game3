#pragma once
#include <Struct.h>

//プレイヤーの弾のクラス
class Bullet {
public:

	int bulletMax;
	int bulletCount;
	bool isShot[10];
	Transform bullet_[10];

public:

	//コンストラクタ
	Bullet();

	//メンバ関数
	void Update(char* keys);
	void Draw();
};