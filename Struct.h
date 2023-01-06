#pragma once

//プレイヤー構造体
typedef struct Player_ {
	int x;
	int y;
	int radius;
	int speed;
};

//弾の構造体
typedef struct Bullet_ {
	int x;
	int y;
	int radius;
	int speed;
	int isShot;
};

//敵の構造体
typedef struct Enemy_ {
	int x;
	int y;
	int radius;
	int speed;
	int hp;
};