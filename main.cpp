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

	//スクロール
	int scroll = 0;
	int scrollspeed = 6;

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
			if (player->player_.x > 800) {
				player->player_.x = 800;
			}
			//スクロール
			if (player->player_.x - scroll <= 400) {
				scroll -= scrollspeed;
			}
			if (player->player_.x >= 400) {
				scroll += scrollspeed;
			}
			//画面スクロール
			if (scroll > 1940) {
				scroll = 1940;
			}
			if (scroll < 0) {
				scroll = 0;
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
						Novice::DrawSprite(x * 32 - scroll , y * 32, box, 1, 1, 0, WHITE);
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
