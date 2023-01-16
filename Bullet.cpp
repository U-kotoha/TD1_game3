#include <Novice.h>
#include <Bullet.h>

Bullet::Bullet() {
	//‰Šú‰»
	bulletMax = 5;
	bulletCount = 0;

	for (int i = 0; i < bulletMax; i++) {
		//’e‚Ì‰Šú‰»
		bullet_[i].x = -100;
		bullet_[i].y = -100;
		bullet_[i].radius = 10;
		bullet_[i].speed = 10;
		isShot[i] = false;
	}
}

void Bullet::Update(char* keys) {
	//•¡”‚Ì’e‚Ìˆ—
	for (int i = 0; i < bulletMax; i++) {
		if (isShot[i] == true) {
			if (bullet_[i].x > (0 - bullet_[i].radius)) {
				bullet_[i].x += bullet_[i].speed;
			}
			if (bullet_[i].x >= 980) {
				bullet_[i].x = -100;
				isShot[i] = false;
			}
		}
	}
}

void Bullet::Draw() {
	int PlayerBullet = Novice::LoadTexture("./Resource/bullet.png");

	//’e‚Ì•`‰æ
	for (int i = 0; i < bulletMax; i++) {
		if (isShot[i] == true) {
			Novice::DrawEllipse(bullet_[i].x, bullet_[i].y,
				bullet_[i].radius, bullet_[i].radius, 0.0f, 0x00, kFillModeSolid);
			Novice::DrawSprite(bullet_[i].x - 15, bullet_[i].y - 15, PlayerBullet, 1, 1, 0.0f, WHITE);
		}
	}
}