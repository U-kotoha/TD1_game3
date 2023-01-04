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

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 960, 640);

	// キー入力結果を受け取る箱
	char keys[256] = {0};
	char preKeys[256] = {0};

	//変数宣言
	int jump = 0;
	int point = 0;
	float yadd = 0.0f;
	float down = 0.0f;

	//インスタンス
	Player* player = new Player(400, 505, 40, 5);
	Bullet* bullet = new Bullet;

	//マップチップ
	const int MapchipX = 30;
	const int MapchipY = 20;

	int box = Novice::LoadTexture("./Resource/block.png");
	int map[MapchipY][MapchipX] = {};

	enum MapInfo {
		NONE, //0
		BOX  //1
	};

	//ファイル読み込み
	FILE* fp1 = nullptr;
	char filename1[] = "ステージ1.csv";
	int err1 = fopen_s(&fp1, "ステージ1.csv", "r");

	for (int i = 0; i < MapchipY; i++) {
		for (int j = 0; j < MapchipX; j++) {
			fscanf_s(fp1, "%d,", &map[i][j]);
		}
	}

	fclose(fp1);
	const int mapChipSize = 32;

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

			//移動範囲
			if (player->player_.x > 920) {
				player->player_.x = 920;
			}
			if (player->player_.x < 40) {
				player->player_.x = 40;
			}

			//ジャンプ
			if (keys[DIK_W] && preKeys[DIK_W] == 0) {
				jump = 1;
			}
			if (jump == 1) {
				yadd = -5.0f;
				down = +5.0f;
			}
			if (jump == 1) {
				if (point == 0) {
					player->player_.y += yadd;
				}
			}
			if (jump == 1) {
				if (player->player_.y <= 405) {
					point = 1;
				}
			}
			if (point == 1) {
				player->player_.y += down;
			}
			if (player->player_.y == 505) {
				jump = 0;
				point = 0;
			}

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
						Novice::DrawSprite(x * 32, y * 32, box, 1, 1, 0, WHITE);
					}
				}
			}

			Novice::ScreenPrintf(0, 0, "posX = %d", player->player_.x);
			Novice::ScreenPrintf(0, 30, "posY = %d", player->player_.y);

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
