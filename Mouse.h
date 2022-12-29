#pragma once
#include <Struct.h>

//マウスのクラス
class Mouse {
public:

	Mouse_ mouse_;

public:

	Mouse();

	//マウス操作の関数
	void MouseOperation(Mouse& mouse);

	//選択画面描画の関数
	void Select(float m, Mouse& mouse);

	//ゲームオーバー
	void SpriteGameover(Mouse& mouse, char keys[]);

	//ゲームクリア
	void SpriteGameclear(Mouse& mouse, char keys[]);
};