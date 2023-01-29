#include <Novice.h>
#include <Player.h>

Player::Player() {
	//������
	player_hp = 1;
	player_.x = 100;
	player_.y = 505;
	player_.radius = 40;
	player_.speed = 5;

	P_Bullet = new Bullet;
}

Player::~Player() {
	//�|�C���^�폜
	delete P_Bullet;
}

void Player::Move(Bullet* P_Bullet, char* keys) {
	//�v���C���[�̈ړ�����
	if (keys[DIK_A]) {
		player_.x -= player_.speed;
	};
	if (keys[DIK_D]) {
		player_.x += player_.speed;
	};

	//�e�̔��ˏ���
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
}

void Player::Draw(Bullet* P_Bullet) {
	//�v���C���[�̕`��
	Novice::DrawEllipse(player_.x, player_.y, player_.radius, player_.radius, 0.0f, WHITE, kFillModeSolid);
	//�e�̕`��
	P_Bullet->Draw();
}