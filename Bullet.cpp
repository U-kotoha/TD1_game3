#include <Novice.h>
#include <Bullet.h>

Bullet::Bullet() {
	//èâä˙âª
	bulletMax = 10;
	bulletCount = 0;

	for (int i = 0; i < bulletMax; i++) {
		bullet_[i].x = -100;
		bullet_[i].y = -100;
		bullet_[i].radius = 10;
		bullet_[i].speed = 10;
		bullet_[i].isShot = false;
	}
}

void Bullet::Update(char* keys) {
	//à⁄ìÆèàóù
	for (int i = 0; i < bulletMax; i++) {
		if (bullet_[i].isShot == true) {
			if (bullet_[i].x > (0 - bullet_[i].radius)) {
				bullet_[i].x += bullet_[i].speed;
			}
			if (bullet_[i].x <= (0 - bullet_[i].radius)) {
				bullet_[i].x = -100;
				bullet_[i].isShot = false;
			}
		}
	}
}

void Bullet::Draw() {
	//ï`âÊèàóù
	for (int i = 0; i < bulletMax; i++) {
		if (bullet_[i].isShot == true) {
			Novice::DrawEllipse(bullet_[i].x, bullet_[i].y, bullet_[i].radius, bullet_[i].radius, 0.0f, WHITE, kFillModeSolid);
		}
	}
}