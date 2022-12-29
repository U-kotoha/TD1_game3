#pragma once
#include <Struct.h>

//弾のクラス
class Bullet {
public:

	int bulletMax;
	int bulletCount;
	Bullet_ bullet_[10];

public:

	//コンストラクタ
	Bullet();

	//メンバ関数
	void Update(char* keys);
	void Draw();
};