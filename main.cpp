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
	title, rule, stage1, stage2, stage3, gameover, gameclear
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

	//インスタンス
	Player* player = new Player;
	Bullet* bullet = new Bullet;
	Enemy* enemy = new Enemy;

	//変数宣言
	int player_hp = 1;
	int enemybullet = 0;
	int enemybulletX = -100;
	int enemybulletY = -100;
	int enemybulletRadius = 10;
	int enemybulletspeed = 8;

	//マウス変数
	int x = 0;
	int y = 0;

	//ジャンプ変数
	int jump = 0;
	int point = 0;
	float yadd = 0.0f;
	float down = 0.0f;

	//マップチップ
	const int MapchipX = 30;
	const int MapchipY = 20;
	const int mapChipSize = 32;

	int map[MapchipY][MapchipX] = {};

	enum MapInfo {
		NONE, //0
		BOX  //1
	};

	//リソース読み込み
	int box = Novice::LoadTexture("./Resource/block.png");
	int gametitle = Novice::LoadTexture("./Resource/title.png");
	int gamerule = Novice::LoadTexture("./Resource/rule.png");
	int playgame = Novice::LoadTexture("./Resource/stage.png");
	int enemyBullet = Novice::LoadTexture("./Resource/enemybullet.png");

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
		case title:   //タイトル

			//マウス位置取得
			Novice::GetMousePosition(&x, &y);

			//シーン切り替え
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
				nowMode = rule;
			}
			break;

		case rule:   //ルール
			
			//シーン切り替え
			if (keys[DIK_SPACE] && preKeys[DIK_SPACE] == 0) {
				nowMode = stage1;
			}
			break;
		
		case stage1:   //メイン

			//プレイヤーの動き
			player->Move(bullet, keys);

			//プレイヤーの移動範囲
			if (player->player_.x > 920) {
				player->player_.x = 920;
			}
			if (player->player_.x < 40) {
				player->player_.x = 40;
			}
			if (enemy->enemy_.hp != 0) {
				if (player->player_.x > 620) {
					player->player_.x = 620;
				}
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

			//プレイヤーの攻撃と敵の当たり判定
			if (enemy->enemy_.hp != 0) {
				for (int i = 0; i < bullet->bulletMax; i++) {
					if (bullet->bullet_[i].isShot == true) {
						float dx = bullet->bullet_[i].x - enemy->enemy_.x;
						float dy = bullet->bullet_[i].y - enemy->enemy_.y;
						float d = sqrtf(dx * dx + dy * dy);

						if (d <= bullet->bullet_[i].radius + enemy->enemy_.radius) {
							bullet->bullet_[i].isShot = 0;
							enemy->OnCollision();
						}
					}
				}
			}

			//シーン切り替え
			if (player->player_.x >= 910) {
				nowMode = stage2;
				player->player_.x = 40;
				player->player_.y = 505;
				enemy->enemy_.hp = 10;
			}
			break;

		case stage2:   //メイン

			//プレイヤーの動き
			player->Move(bullet, keys);

			//プレイヤーの移動範囲
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

			//プレイヤーの攻撃と敵の当たり判定
			if (enemy->enemy_.hp != 0) {
				for (int i = 0; i < bullet->bulletMax; i++) {
					if (bullet->bullet_[i].isShot == true) {
						float dx = bullet->bullet_[i].x - enemy->enemy_.x;
						float dy = bullet->bullet_[i].y - enemy->enemy_.y;
						float d = sqrtf(dx * dx + dy * dy);

						if (d <= bullet->bullet_[i].radius + enemy->enemy_.radius) {
							bullet->bullet_[i].isShot = 0;
							enemy->OnCollision();
						}
					}
				}
			}

			//敵の攻撃
			if (enemy->enemy_.hp != 0) {
				if (enemybullet == 0) {
					enemybullet = 1;
					enemybulletX = enemy->enemy_.x-40;
					enemybulletY = enemy->enemy_.y;
				}
				if (enemybullet == 1) {
					enemybulletX -= enemybulletspeed;
				}
				if (enemybulletX < 40) {
					enemybullet = 0;
					enemybulletX = enemy->enemy_.x-40;
					enemybulletY = enemy->enemy_.y;
				}
			}
			if (enemy->enemy_.hp == 0) {
				enemybullet = 0;
			}

			//敵の攻撃とプレイヤーの当たり判定
			if (enemybullet == 1) {
				float enemybullet_player_X = enemybulletX - player->player_.x;
				float enemybullet_player_Y = enemybulletY - player->player_.y;
				float d2 = sqrtf(enemybullet_player_X * enemybullet_player_X + enemybullet_player_Y * enemybullet_player_Y);

				if (d2 <= enemybulletRadius + player->player_.radius) {
					enemybullet = 0;
					player_hp = 0;
				}
			}

			//シーン切り替え
			if (player->player_.x >= 910) {
				nowMode = stage3;
				player->player_.x = 40;
				player->player_.y = 505;
				enemy->enemy_.hp = 10;
			}
			if (player_hp == 0) {
				nowMode = gameover;
			}
			break;

		case stage3:   //メイン

			//プレイヤーの動き
			player->Move(bullet, keys);

			//プレイヤーの移動範囲
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
			if (player_hp == 0) {
				nowMode = gameover;
			}

			break;

		case gameover:   //ゲームオーバー

			//シーン切り替え
			if (keys[DIK_LSHIFT] && preKeys[DIK_LSHIFT] == 0) {
				nowMode = rule;
				player_hp = 1;
			}
			break;

		case gameclear:   //クリア

			//シーン切り替え
			if (keys[DIK_LSHIFT] && preKeys[DIK_LSHIFT] == 0) {
				nowMode = title;
				player_hp = 1;
			}
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
		case title:   //タイトル

			//背景
			Novice::DrawSprite(0, 0, gametitle, 1, 1, 0, WHITE);

			//デバッグ
			//Novice::ScreenPrintf(0, 0, "Mouse X : %d", x);
			//Novice::ScreenPrintf(0, 30, "Mouse Y : %d", y);
			break;

		case rule:  //ルール

			//背景
			Novice::DrawSprite(0, 0, gamerule, 1, 1, 0, WHITE);
			break;

		case stage1:   //メイン

			//背景
			Novice::DrawSprite(0, 0, playgame, 1, 1, 0, WHITE);

			//プレイヤー
			player->Draw(bullet);

			//マップ
			for (int y = 0; y < MapchipY; y++) {
				for (int x = 0; x < MapchipX; x++) {
					if (map[y][x] == BOX) {
						Novice::DrawSprite(x * 32, y * 32, box, 1, 1, 0, WHITE);
					}
				}
			}

			//敵
			if (enemy->enemy_.hp > 0) {
				enemy->Draw();
			}

			//デバッグ
			Novice::ScreenPrintf(0, 0, "posX = %d", player->player_.x);
			Novice::ScreenPrintf(0, 30, "posY = %d", player->player_.y);
			//Novice::ScreenPrintf(0, 60, "enemyHP = %d", enemy->enemy_.hp);
			break;

		case stage2:   //メイン

			//背景
			Novice::DrawSprite(0, 0, playgame, 1, 1, 0, WHITE);

			//プレイヤー
			player->Draw(bullet);

			//マップ
			for (int y = 0; y < MapchipY; y++) {
				for (int x = 0; x < MapchipX; x++) {
					if (map[y][x] == BOX) {
						Novice::DrawSprite(x * 32, y * 32, box, 1, 1, 0, WHITE);
					}
				}
			}

			//敵
			if (enemy->enemy_.hp > 0) {
				enemy->Draw();
			}
			if (enemybullet == 1) {
				Novice::DrawEllipse(enemybulletX, enemybulletY, enemybulletRadius, enemybulletRadius, 0.0f, RED, kFillModeSolid);
				Novice::DrawSprite(enemybulletX-15, enemybulletY-15, enemyBullet, 1, 1, 0, WHITE);
			}

			//デバッグ
			//Novice::ScreenPrintf(0, 0, "posX = %d", player->player_.x);
			//Novice::ScreenPrintf(0, 30, "posY = %d", player->player_.y);
			break;

		case stage3:   //メイン

			//背景
			Novice::DrawSprite(0, 0, playgame, 1, 1, 0, WHITE);

			//プレイヤー
			player->Draw(bullet);

			//マップ
			for (int y = 0; y < MapchipY; y++) {
				for (int x = 0; x < MapchipX; x++) {
					if (map[y][x] == BOX) {
						Novice::DrawSprite(x * 32, y * 32, box, 1, 1, 0, WHITE);
					}
				}
			}

			//デバッグ
			//Novice::ScreenPrintf(0, 0, "posX = %d", player->player_.x);
			//Novice::ScreenPrintf(0, 30, "posY = %d", player->player_.y);
			break;

		case gameover:   //ゲームオーバー

			//背景

			break;

		case gameclear:   //クリア

			//背景

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
	delete enemy;

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
