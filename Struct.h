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
