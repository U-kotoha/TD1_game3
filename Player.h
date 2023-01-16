#pragma once
#include <Struct.h>
#include <Bullet.h>

//プレイヤーのクラス
class Player {
public:

	int player_hp;

	Transform player_;
	Bullet* P_Bullet;

public:

	//コンストラクタ
	Player();
	//デストラクタ
	~Player();

	//メンバ関数
	void Move(Bullet* P_Bullet, char* keys);
	void Draw(Bullet* P_Bullet);
};