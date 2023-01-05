#include <Novice.h>
#include <stdio.h>
#include <math.h>
#define _USE_MATH_DEFINES

#include <Player.h>
#include <Bullet.h>
#include <Enemy.h>

const char kWindowTitle[] = "GC1A_05_ウブカタコトハ_タイトル";

//シーン管理
enum modeName {
	title, stage1, stage2, stage3, gameover, gameclear
};
int nowMode = title;

//マウス位置の取得
static int GetMousePosition(int* positionX, int* positionY);

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
	int HP = 1;

	//マウス
	int x = 0;
	int y = 0;

	//インスタンス
	Player* player = new Player;
	Bullet* bullet = new Bullet;
	Enemy* enemy = new Enemy;

	//マップチップ
	const int MapchipX = 30;
	const int MapchipY = 20;
	const int mapChipSize = 32;

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
			Novice::GetMousePosition(&x, &y);

			//シーン切り替え
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
				nowMode = stage1;
			}

			break;

		case stage1:	//メイン
			player->Move(bullet, keys);

			//移動範囲
			if (player->player_.x > 920) {
				player->player_.x = 920;
			}
			if (player->player_.x < 40) {
				player->player_.x = 40;
			}

			//ジャンプ
			if (keys[DIK_SPACE]&& preKeys[DIK_SPACE] == 0) {
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

			//当たり判定
			float dx = player->player_.x - enemy->enemy_.x;
			float dy = player->player_.y - enemy->enemy_.y;
			float distance = sqrtf(dx * dx + dy * dy);

			if (distance <= player->player_.radius * enemy->enemy_.radius) {
				enemy->OnCollision();
			}

			//シーン切り替え
			if (player->player_.x >= 910) {
				nowMode = stage2;
				player->player_.x = 40;
				player->player_.y = 505;
			}

			break;

		case stage2:	//メイン
			player->Move(bullet, keys);

			//移動範囲
			if (player->player_.x > 920) {
				player->player_.x = 920;
			}
			if (player->player_.x < 40) {
				player->player_.x = 40;
			}

			//ジャンプ
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
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

			//シーン切り替え
			if (HP == 0) {
				nowMode = gameover;
			}

			break;

		case stage3:	//メイン
			player->Move(bullet, keys);

			//移動範囲
			if (player->player_.x > 920) {
				player->player_.x = 920;
			}
			if (player->player_.x < 40) {
				player->player_.x = 40;
			}

			//ジャンプ
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
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

			//シーン切り替え
			if (HP == 0) {
				nowMode = gameover;
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

			//デバッグ
			Novice::ScreenPrintf(0, 0, "Mouse X : %d", x);
			Novice::ScreenPrintf(0, 30, "Mouse Y : %d", y);

			break;

		case stage1: //メイン
			player->Draw(bullet);

			for (int y = 0; y < MapchipY; y++) {
				for (int x = 0; x < MapchipX; x++) {
					if (map[y][x] == BOX) {
						Novice::DrawSprite(x * 32, y * 32, box, 1, 1, 0, WHITE);
					}
				}
			}
			enemy->Draw();

			//デバッグ
			Novice::ScreenPrintf(0, 0, "posX = %d", player->player_.x);
			Novice::ScreenPrintf(0, 30, "posY = %d", player->player_.y);

			break;

		case stage2: //メイン
			player->Draw(bullet);

			for (int y = 0; y < MapchipY; y++) {
				for (int x = 0; x < MapchipX; x++) {
					if (map[y][x] == BOX) {
						Novice::DrawSprite(x * 32, y * 32, box, 1, 1, 0, WHITE);
					}
				}
			}

			//デバッグ
			Novice::ScreenPrintf(0, 0, "posX = %d", player->player_.x);
			Novice::ScreenPrintf(0, 30, "posY = %d", player->player_.y);

			break;

		case stage3: //メイン
			player->Draw(bullet);

			for (int y = 0; y < MapchipY; y++) {
				for (int x = 0; x < MapchipX; x++) {
					if (map[y][x] == BOX) {
						Novice::DrawSprite(x * 32, y * 32, box, 1, 1, 0, WHITE);
					}
				}
			}

			//デバッグ
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
