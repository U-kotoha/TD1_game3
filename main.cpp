#include <Novice.h>
#include <stdio.h>
#include <Player.h>
#include <Bullet.h>

const char kWindowTitle[] = "GC1A_05_ウブカタコトハ_タイトル";

//シーン管理
enum modeName {
	title, stage, gameover, gameclear
};
int nowMode = stage;

//マウス
typedef struct Mouse {
	int posX; //マウスのX座標
	int posY; //マウスのY座標
	int clickCount; //カウント
	bool isLeftClick; //左クリック判定
	bool isRightClick; //右クリック判定
};

//マウス操作の関数
void MouseOperation(Mouse& mouse);

//選択画面描画の関数
void Select(float m, Mouse& mouse);

//ゲームオーバー
void SpriteGameover(Mouse& mouse, char keys[]);

//ゲームクリア
void SpriteGameclear(Mouse& mouse, char keys[]);

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1000, 600);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	//インスタンス
	Player* player = new Player(600, 500, 50, 5);
	Bullet* bullet = new Bullet;

	//マウス定義
	Mouse mouse {
		0, //posX
		0, //posY
		0, //clickCount
		false, //isLeftClick
		false, //isRightClick
	};
	float m = 0;

	//マップチップ
	const int MapchipX = 48;
	const int MapchipY = 15;

	int box = Novice::LoadTexture("./Resource/block.png");
	int map[MapchipY][MapchipX] = {};

	enum MapInfo {
		NONE, //0
		BOX  //1
	};

	FILE* fp1 = nullptr;
	char filename1[] = "ステージ - ステージ1.csv";
	int err1 = fopen_s(&fp1, "ステージ - ステージ1.csv", "r");

	for (int i = 0; i < MapchipY; i++) {
		for (int j = 0; j < MapchipX; j++) {
			fscanf_s(fp1, "%d,", &map[i][j]);
		}
	}

	fclose(fp1);
	const int mapChipSize = 64;

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		memcpy(preKeys, keys, 256);
		Novice::GetHitKeyStateAll(keys);

		///
		/// ↓更新処理ここから
		///
		switch (nowMode)
		{
		case title:	//タイトル

			break;

		case stage:	//メイン
			player->Move(bullet, keys);

			break;

		case gameover:	//ゲームオーバー

			break;

		case gameclear:	//クリア

			break;
		}
		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///
		switch (nowMode)
		{
		case title: //タイトル

			break;

		case stage: //メイン
			player->Draw(bullet);

			for (int y = 0; y < MapchipY; y++) {
				for (int x = 0; x < MapchipX; x++) {
					if (map[y][x] == BOX) {
						Novice::DrawSprite(x * 64, y * 64, box, 1, 1, 0, WHITE);
					}
				}
			}
			break;

		case gameover: //ゲームオーバー

			break;

		case gameclear: //クリア

			break;
		}
		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (preKeys[DIK_ESCAPE] == 0 && keys[DIK_ESCAPE] != 0) {
			break;
		}
	}

	delete player;
	delete bullet;

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
