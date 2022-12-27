#pragma once

//構造体
typedef struct Vector2
{
	float x;
	float y;
};

//マウス
typedef struct Mouse
{
	int posX; //マウスのX座標
	int posY; //マウスのY座標
	int clickCount; //カウント
	bool isLeftClick; //左クリック判定
	bool isRightClick; //右クリック判定
};

