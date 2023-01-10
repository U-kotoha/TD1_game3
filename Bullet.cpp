#include <Novice.h>
#include <Bullet.h>

Bullet::Bullet() {
	//初期化
	bulletMax = 5;
	bulletCount = 0;

	for (int i = 0; i < bulletMax; i++) {
		//弾の初期化
		bullet_[i].x = -100;
		bullet_[i].y = -100;
		bullet_[i].radius = 10;
		bullet_[i].speed = 10;
		bullet_[i].isShot = false;
	}
}

void Bullet::Update(char* keys) {
	//弾の処理
	for (int i = 0; i < bulletMax; i++) {
		if (bullet_[i].isShot == true) {
			if (bullet_[i].x > (0 - bullet_[i].radius)) {
				bullet_[i].x += bullet_[i].speed;
			}
			if (bullet_[i].x >= 980) {
				bullet_[i].x = -100;
				bullet_[i].isShot = false;
			}
		}
	}
}

void Bullet::Draw() {
	int playerBullet = Novice::LoadTexture("./Resource/bullet.png");

	//描画処理
	for (int i = 0; i < bulletMax; i++) {
		if (bullet_[i].isShot == true) {
			Novice::DrawEllipse(bullet_[i].x, bullet_[i].y, bullet_[i].radius, bullet_[i].radius, 0.0f, 0x00, kFillModeSolid);
			Novice::DrawSprite(bullet_[i].x-15, bullet_[i].y-15, playerBullet, 1, 1, 0.0f, WHITE);
		}
	}
}