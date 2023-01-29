#include <Novice.h>
#include <EnemyBullet.h>

EnemyBullet::EnemyBullet() {
	//èâä˙âª
	enemy_isShot = false;
	enemybullet_.x = -100;
	enemybullet_.y = -100;
	enemybullet_.radius = 10;
	enemybullet_.speed = 8;
}

void EnemyBullet::Draw() {
	if (enemy_isShot == true) {
		Novice::DrawEllipse(enemybullet_.x, enemybullet_.y,enemybullet_.radius, enemybullet_.radius, 0.0f, RED, kFillModeSolid);
	}
}