#pragma once
#include <Struct.h>
#include <Bullet.h>

//プレイヤーのクラス
class Player {
public:

	//メンバ変数
	int player_hp;
	Transform player_;
	Bullet* P_Bullet;

public:

	//コンストラクタ
	Player();
	//デストラクタ
	~Player();

	//メンバ関数
	void Move(Bullet* P_Bullet, char* keys, char* preKeys);
	void Draw(Bullet* P_Bullet);
};