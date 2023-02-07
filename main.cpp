#include <Novice.h>
#include <stdio.h>
#include <math.h>
#define _USE_MATH_DEFINES

#include <Player.h>
#include <Bullet.h>
#include <Enemy.h>
#include <EnemyBullet.h>
#include <EnemyBoss.h>

const char kWindowTitle[] = "SNOW BALL";

//シーン管理
enum modeName {
	title, rule, stage1, stage2, stage3, gameover, gameclear
};
int nowMode = title;

//マウス位置の取得
static int GetMousePosition(int* positionX, int* positionY);

//マウスカーソル表示非表示
static void SetMouseCursorVisibility(int visibility);

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
	Enemy* enemy2 = new Enemy;
	EnemyBoss* enemyboss = new EnemyBoss;
	EnemyBullet* enemybullet = new EnemyBullet;

	//マウス変数
	int x = 0;
	int y = 0;
	int visibility = 0;

	//ジャンプ変数
	int jump = 0;
	int point = 0;
	float yadd = 0.0f;
	float down = 0.0f;

	//マップチップ
	const int MapchipX = 30;
	const int MapchipY = 20;
	const int mapChipSize = 32;
	int randX = 0;
	int randY = 0;

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
	int playgame_1 = Novice::LoadTexture("./Resource/stage_1.png");
	int gameovergamen = Novice::LoadTexture("./Resource/gameover.png");
	int gamecleargamen = Novice::LoadTexture("./Resource/gameclear.png");
	int playerHP3 = Novice::LoadTexture("./Resource/HP3.png");
	int playerHP2 = Novice::LoadTexture("./Resource/HP2.png");
	int playerHP1 = Novice::LoadTexture("./Resource/HP1.png");

	//サウンド読み込み
	int soundHandle = -1;
	int titlesound = Novice::LoadAudio("./Resource/title.wav");

	//ファイル読み込み
	FILE* fp1 = nullptr;
	char filename1[] = "ステージ.csv";
	int err1 = fopen_s(&fp1, "ステージ.csv", "r");

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

			//サウンド
			if (!Novice::IsPlayingAudio(soundHandle) || soundHandle == -1) {
				soundHandle = Novice::PlayAudio(titlesound, true, 0.5);
			}

			//マウス位置取得
			Novice::GetMousePosition(&x, &y);

			//マウス非表示
			visibility = visibility ^ 0; //xor演算子
			Novice::SetMouseCursorVisibility(visibility);

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

			//サウンド
			Novice::StopAudio(titlesound);

			//プレイヤーの動き
			player->Move(bullet, keys, preKeys);

			//敵がいるときは前に進めない
			if (enemy->enemy_hp != 0) {
				if (player->player_.x > 500) {
					player->player_.x = 500;
				}
			}

			//プレイヤーの攻撃と敵の当たり判定
			if (enemy->enemy_hp != 0) {
				for (int i = 0; i < bullet->bulletMax; i++) {
					if (bullet->isShot[i] == true) {
						float dx = bullet->bullet_[i].x - enemy->enemy_.x;
						float dy = bullet->bullet_[i].y - enemy->enemy_.y;
						float d = sqrtf(dx * dx + dy * dy);

						if (d <= bullet->bullet_[i].radius + enemy->enemy_.radius) {
							bullet->isShot[i] = false;
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
				for (int i = 0; i < bullet->bulletMax; i++) {
					bullet->isShot[i] = false;
				}
			}
			break;

		case stage2:   //メイン

			//プレイヤーの動き
			player->Move(bullet, keys, preKeys);

			//敵がいるときは前に進めない
			if (enemy2->enemy_hp != 0) {
				if (player->player_.x > 500) {
					player->player_.x = 500;
				}
			}

			//敵の攻撃
			if (enemy2->enemy_hp != 0) {
				enemy2->Update();
			}

			//プレイヤーの攻撃と敵の当たり判定
			if (enemy2->enemy_hp != 0) {
				for (int i = 0; i < bullet->bulletMax; i++) {
					if (bullet->isShot[i] == true) {
						float dx = bullet->bullet_[i].x - enemy2->enemy_.x;
						float dy = bullet->bullet_[i].y - enemy2->enemy_.y;
						float d = sqrtf(dx * dx + dy * dy);

						if (d <= bullet->bullet_[i].radius + enemy2->enemy_.radius) {
							bullet->isShot[i] = 0;
							enemy2->OnCollision();
						}
					}
				}
			}

			//敵の攻撃とプレイヤーの当たり判定
			if (enemy2->enemy_hp != 0) {
				if (enemy2->E_Bullet->enemy_isShot == true) {
					float enemybullet_player_X = enemy2->E_Bullet->enemybullet_.x - player->player_.x;
					float enemybullet_player_Y = enemy2->E_Bullet->enemybullet_.y - player->player_.y;
					float d2 = sqrtf(enemybullet_player_X * enemybullet_player_X + enemybullet_player_Y * enemybullet_player_Y);

					if (d2 <= enemy2->E_Bullet->enemybullet_.radius + player->player_.radius) {
						enemy2->E_Bullet->enemy_isShot = false;
						player->player_hp -= 1;
					}
				}
			}

			//シーン切り替え
			if (player->player_.x >= 910) {
				nowMode = stage3;
				player->player_.x = 40;
				player->player_.y = 505;
				for (int i = 0; i < bullet->bulletMax; i++) {
					bullet->isShot[i] = false;
				}
			}

			//ゲームオーバー処理
			if (player->player_hp == 0) {
				nowMode = gameover;
				player->player_.x = 100;
				player->player_.y = 505;
				for (int i = 0; i < bullet->bulletMax; i++) {
					bullet->isShot[i] = false;
				}
				enemy2->E_Bullet->enemy_isShot = false;
			}
			break;

		case stage3:   //メイン

			randX = rand() % 11 - 5;
			randY = rand() % 11 - 5;
			
			//プレイヤーの動き
			player->Move(bullet, keys, preKeys);

			//敵がいるときは前に進めない
			if (enemyboss->enemyboss_hp != 0) {
				if (player->player_.x > 500) {
					player->player_.x = 500;
				}
			}

			//敵の攻撃
			if (enemyboss->enemyboss_hp != 0) {
				enemyboss->Update();
			}

			//プレイヤーの攻撃と敵の当たり判定
			if (enemyboss->enemyboss_hp != 0) {
				for (int i = 0; i < bullet->bulletMax; i++) {
					if (bullet->isShot[i] == true) {
						float dx2 = bullet->bullet_[i].x - enemyboss->enemyboss_.x;
						float dy2 = bullet->bullet_[i].y - enemyboss->enemyboss_.y;
						float d_2 = sqrtf(dx2 * dx2 + dy2 * dy2);

						if (d_2 <= bullet->bullet_[i].radius + enemyboss->enemyboss_.radius) {
							bullet->isShot[i] = 0;
							enemyboss->OnCollision();
						}
					}
				}
			}

			//敵の攻撃とプレイヤーの当たり判定
			if (enemyboss->enemyboss_hp != 0) {
				if (enemyboss->E_Bullet->enemy_isShot == true) {
					float enemybullet_player_X2 = enemyboss->E_Bullet->enemybullet_.x - player->player_.x;
					float enemybullet_player_Y2 = enemyboss->E_Bullet->enemybullet_.y - player->player_.y;
					float d3 = sqrtf(enemybullet_player_X2 * enemybullet_player_X2 + enemybullet_player_Y2 * enemybullet_player_Y2);

					if (d3 <= enemyboss->E_Bullet->enemybullet_.radius + player->player_.radius) {
						enemyboss->E_Bullet->enemy_isShot = false;
						player->player_hp -= 1;
					}
				}
			}

			//シーン切り替え
			if (player->player_.x >= 910) {
				nowMode = gameclear;
				player->player_.x = 40;
				player->player_.y = 505;
				for (int i = 0; i < bullet->bulletMax; i++) {
					bullet->isShot[i] = false;
				}
			}
			
			//ゲームオーバー処理
			if (player->player_hp == 0) {
				nowMode = gameover;
				player->player_.x = 100;
				player->player_.y = 505;
				for (int i = 0; i < bullet->bulletMax; i++) {
					bullet->isShot[i] = false;
				}
				enemyboss->E_Bullet->enemy_isShot = false;
			}

			break;

		case gameover:   //ゲームオーバー

			//シーン切り替え
			if (keys[DIK_LSHIFT] && preKeys[DIK_LSHIFT] == 0) {
				nowMode = rule;
				player->player_hp = 3;
				enemy->enemy_hp = 10;
				enemy2->enemy_hp = 10;
				enemyboss->enemyboss_hp = 10;
			}
			break;

		case gameclear:   //クリア

			//シーン切り替え
			if (keys[DIK_LSHIFT] && preKeys[DIK_LSHIFT] == 0) {
				nowMode = title;
				player->player_hp = 3;
				enemy->enemy_hp = 10;
				enemy2->enemy_hp = 10;
				enemyboss->enemyboss_hp = 10;
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

#ifdef _DEBUG //デバッグ
			Novice::ScreenPrintf(0, 0, "Mouse X : %d", x);
			Novice::ScreenPrintf(150, 0, "Mouse Y : %d", y);
#endif 
			break;

		case rule:  //ルール

			//背景
			Novice::DrawSprite(0, 0, gamerule, 1, 1, 0, WHITE);
			break;

		case stage1:   //メイン

			//背景
			Novice::DrawSprite(0, 0, playgame, 1, 1, 0, WHITE);
			if (enemy->enemy_hp != 0) {
				Novice::DrawSprite(0, 0, playgame_1, 1, 1, 0, WHITE);
			}
			if (player->player_hp == 3) {
				Novice::DrawSprite(0, 0, playerHP3, 1, 1, 0, WHITE);
			}
			if (player->player_hp == 2) {
				Novice::DrawSprite(0, 0, playerHP2, 1, 1, 0, WHITE);
			}
			if (player->player_hp == 1) {
				Novice::DrawSprite(0, 0, playerHP1, 1, 1, 0, WHITE);
			}

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
			if (enemy->enemy_hp > 0) {
				enemy->Draw();
			}

#ifdef _DEBUG //デバッグ
			Novice::ScreenPrintf(0, 0, "posX = %d", player->player_.x);
			Novice::ScreenPrintf(0, 30, "posY = %d", player->player_.y);
			Novice::ScreenPrintf(0, 60, "enemyHP = %d", enemy->enemy_hp);
			Novice::ScreenPrintf(0, 90, "HP = %d", player->player_hp);
#endif 
			break;

		case stage2:   //メイン

			//背景
			Novice::DrawSprite(0, 0, playgame, 1, 1, 0, WHITE);
			if (player->player_hp == 3) {
				Novice::DrawSprite(0, 0, playerHP3, 1, 1, 0, WHITE);
			}
			if (player->player_hp == 2) {
				Novice::DrawSprite(0, 0, playerHP2, 1, 1, 0, WHITE);
			}
			if (player->player_hp == 1) {
				Novice::DrawSprite(0, 0, playerHP1, 1, 1, 0, WHITE);
			}

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
			if (enemy2->enemy_hp > 0) {
				enemy2->Draw();
			}
			if (enemy2->enemy_hp > 0) {
				if (enemy2->E_Bullet->enemy_isShot == true) {
					enemy2->E_Bullet->Draw();
				}
			}

#ifdef _DEBUG //デバッグ
			Novice::ScreenPrintf(0, 0, "posX = %d", player->player_.x);
			Novice::ScreenPrintf(0, 30, "posY = %d", player->player_.y);
			Novice::ScreenPrintf(0, 60, "enemyHP = %d", enemy2->enemy_hp);
			Novice::ScreenPrintf(0, 90, "HP = %d", player->player_hp);
#endif
			break;

		case stage3:   //メイン
					   
		    //背景
			Novice::DrawSprite(0, 0, playgame, 1, 1, 0, WHITE);
			if (player->player_hp == 3) {
				Novice::DrawSprite(0, 0, playerHP3, 1, 1, 0, WHITE);
			}
			if (player->player_hp == 2) {
				Novice::DrawSprite(0, 0, playerHP2, 1, 1, 0, WHITE);
			}
			if (player->player_hp == 1) {
				Novice::DrawSprite(0, 0, playerHP1, 1, 1, 0, WHITE);
			}

			//プレイヤー
			player->Draw(bullet);

			//マップ
			if (enemyboss->enemyboss_hp != 0) {
				for (int y = 0; y < MapchipY; y++) {
					for (int x = 0; x < MapchipX; x++) {
						if (map[y][x] == BOX) {
							Novice::DrawSprite(x * 32 + randX, y * 32 + randY, box, 1, 1, 0, WHITE);
						}
					}
				}
			}
			if (enemyboss->enemyboss_hp == 0) {
				for (int y = 0; y < MapchipY; y++) {
					for (int x = 0; x < MapchipX; x++) {
						if (map[y][x] == BOX) {
							Novice::DrawSprite(x * 32, y * 32, box, 1, 1, 0, WHITE);
						}
					}
				}
			}

			//敵
			if (enemyboss->enemyboss_hp > 0) {
				enemyboss->Draw();
			}
			if (enemyboss->enemyboss_hp > 0) {
				if (enemyboss->E_Bullet->enemy_isShot == true) {
					enemyboss->E_Bullet->Draw();
				}
			}

#ifdef _DEBUG //デバッグ
			Novice::ScreenPrintf(0, 0, "posX = %d", player->player_.x);
			Novice::ScreenPrintf(0, 30, "posY = %d", player->player_.y);
			Novice::ScreenPrintf(0, 60, "enemyHP = %d", enemyboss->enemyboss_hp);
			Novice::ScreenPrintf(0, 90, "HP = %d", player->player_hp);
#endif
			break;

		case gameover:   //ゲームオーバー

			//背景
			Novice::DrawSprite(0, 0, gameovergamen, 1, 1, 0, WHITE);

			break;

		case gameclear:   //クリア

			//背景
			Novice::DrawSprite(0, 0, gamecleargamen, 1, 1, 0, WHITE);

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
	delete enemy2;
	delete enemyboss;
	delete enemybullet;

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}
