#include <Novice.h>
#include <EnemyBullet.h>

EnemyBullet::EnemyBullet() {
	enemy_isShot = false;
	enemybullet_.x = -100;
	enemybullet_.y = -100;
	enemybullet_.radius = 10;
	enemybullet_.speed = 8;
}

void EnemyBullet::Draw() {
	int ENEMYBULLET = Novice::LoadTexture("./Resource/enemybullet.png");

	if (enemy_isShot == true) {
		Novice::DrawEllipse(enemybullet_.x, enemybullet_.y,
			enemybullet_.radius, enemybullet_.radius, 0.0f, RED, kFillModeSolid);
		Novice::DrawSprite(enemybullet_.x - 15, enemybullet_.y - 15, ENEMYBULLET, 1, 1, 0, WHITE);
	}
}