#include <Novice.h>
#include <Bullet.h>
#include <Player.h>

Player::Player(int x, int y, int radius, int speed) {
	player_.x = 600;
	player_.y = 500;
	player_.radius = 50;
	player_.speed = 5;

	P_Bullet = new Bullet;
}

Player::~Player() {
	//�|�C���^�폜
	delete P_Bullet;
}

void Player::Move(Bullet* P_Bullet, char* keys) {
	player_.speed = 5;

	if (keys[DIK_W]) {
		player_.y -= player_.speed;
	};
	if (keys[DIK_S]) {
		player_.y += player_.speed;
	};
	if (keys[DIK_A]) {
		player_.x -= player_.speed;
	};
	if (keys[DIK_D]) {
		player_.x += player_.speed;
	};

	//���ˏ���
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
	//�v���C���[�̕`��
	Novice::DrawEllipse(player_.x, player_.y, player_.radius, player_.radius, 0.0f, WHITE, kFillModeSolid);
	//�e�̕`��
	P_Bullet->Draw();
}