#include <Novice.h>
#include <Bullet.h>
#include <Player.h>

Player* player = new Player(600, 500, 50, 5);

Player::Player(int x, int y, int radius, int speed) {
	this->player_.x = 600;
	this->player_.y = 500;
	this->player_.radius = 50;
	this->player_.speed = 5;

	P_Bullet = new Bullet;
}

Player::~Player() {
	//ポインタ削除
	delete P_Bullet;
}

void Player::Move(Bullet* P_Bullet, char* keys) {
	player->player_.speed = 5;

	if (keys[DIK_W]) {
		player->player_.y -= player->player_.speed;
	};
	if (keys[DIK_S]) {
		player->player_.y += player->player_.speed;
	};
	if (keys[DIK_A]) {
		player->player_.x -= player->player_.speed;
	};
	if (keys[DIK_D]) {
		player->player_.x += player->player_.speed;
	};

	//発射処理
	for (int i = 0; i < P_Bullet->bulletMax; i++) {
		if (keys[DIK_SPACE] && P_Bullet->bullet_[i].isShot == false && P_Bullet->bulletCount == 0) {
			P_Bullet->bullet_[i].x = player_.x;
			P_Bullet->bullet_[i].y = player_.y;
			P_Bullet->bullet_[i].isShot = true;
			P_Bullet->bulletCount = 10;
		}
	}

	P_Bullet->Update(keys);

	P_Bullet->bulletCount--;
	if (P_Bullet->bulletCount <= 0)
	{
		P_Bullet->bulletCount = 0;
	}
}

void Player::Draw(Bullet* P_Bullet) {
	//プレイヤーの描画
	Novice::DrawEllipse(player->player_.x, player->player_.y, player->player_.radius, player->player_.radius, 0.0f, WHITE, kFillModeSolid);
	//弾の描画
	P_Bullet->Draw();
}