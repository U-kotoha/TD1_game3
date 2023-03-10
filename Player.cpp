#include <Novice.h>
#include <Player.h>

//変数宣言
int jump = 0;
float yadd = 0.0f;
float down = 0.0f;
int point = 0;

Player::Player() {
	//初期化
	player_hp = 3;
	player_.x = 100;
	player_.y = 505;
	player_.radius = 40;
	player_.speed = 5;

	P_Bullet = new Bullet;
}

Player::~Player() {
	//ポインタ削除
	delete P_Bullet;
}

void Player::Move(Bullet* P_Bullet, char* keys, char* preKeys) {
	//プレイヤーの移動処理
	if (keys[DIK_A]) {
		player_.x -= player_.speed;
	};
	if (keys[DIK_D]) {
		player_.x += player_.speed;
	};

	//プレイヤーの移動範囲
	if (player_.x > 920) {
		player_.x = 920;
	}
	if (player_.x < 40) {
		player_.x = 40;
	}

	//弾の発射処理
	for (int i = 0; i < P_Bullet->bulletMax; i++) {
		if (Novice::IsPressMouse(0) && P_Bullet->isShot[i] == false && P_Bullet->bulletCount == 0) {
			P_Bullet->bullet_[i].x = player_.x + 40;
			P_Bullet->bullet_[i].y = player_.y;
			P_Bullet->isShot[i] = true;
			P_Bullet->bulletCount = 10;
		}
	}

	P_Bullet->Update(keys);

	P_Bullet->bulletCount--;
	if (P_Bullet->bulletCount <= 0) {
		P_Bullet->bulletCount = 0;
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
			player_.y += yadd;
		}
	}
	if (jump == 1) {
		if (player_.y <= 400) {
			point = 1;
		}
	}
	if (point == 1) {
		player_.y += down;
	}
	if (player_.y >= 505) {
		jump = 0;
		point = 0;
	}
}

void Player::Draw(Bullet* P_Bullet) {
	//プレイヤーの描画
	int PLAYER = Novice::LoadTexture("./Resource/player.png");
	Novice::DrawSprite(player_.x - 35, player_.y - 25, PLAYER, 1, 1, 0.0f, WHITE);
	//Novice::DrawEllipse(player_.x, player_.y, player_.radius, player_.radius, 0.0f, WHITE, kFillModeSolid);
	
	//弾の描画
	P_Bullet->Draw();
}