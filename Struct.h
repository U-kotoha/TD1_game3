#pragma once

//マウス
typedef struct Mouse
{
	int posX; //マウスのX座標
	int posY; //マウスのY座標
	int clickCount; //カウント
	bool isLeftClick; //左クリック判定
	bool isRightClick; //右クリック判定
};

//構造体
typedef struct Player_ {
	int x;
	int y;
	int radius;
	int speed;
};

typedef struct Bullet_ {
	int x;
	int y;
	int radius;
	int speed;
	int isShot;
};