#include <Novice.h>
#include <Enemy.h>

Enemy::Enemy() {
	enemy_.x = 800;
	enemy_.y = 505;
	enemy_.radius = 40;
	enemy_.speed = 5;
	enemy_.hp = 10;
}

void Enemy::Update() {
	
}

void Enemy::Draw() {
	Novice::DrawEllipse(enemy_.x, enemy_.y, enemy_.radius, enemy_.radius, 0.0f, RED, kFillModeSolid);
}

void Enemy::OnCollision() {
	enemy_.hp -= 1;
}