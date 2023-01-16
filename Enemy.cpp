#include <Novice.h>
#include <Enemy.h>

Enemy::Enemy() {
	enemy_hp = 10;
	enemy_.x = 800;
	enemy_.y = 505;
	enemy_.radius = 40;
	enemy_.speed = 5;

	E_Bullet = new EnemyBullet;
}

Enemy::~Enemy() {
	//ƒ|ƒCƒ“ƒ^íœ
	delete E_Bullet;
}

void Enemy::Update() {

	//“G‚ÌUŒ‚
	if (enemy_hp != 0) {
		if (E_Bullet->enemy_isShot == false) {
			E_Bullet->enemy_isShot = true;
			E_Bullet->enemy_isShot = enemy_.x - 40;
			E_Bullet->enemy_isShot = enemy_.y;
		}
		if (E_Bullet->enemy_isShot == true) {
			E_Bullet->enemybullet_.x -= E_Bullet->enemybullet_.speed;
		}
		if (E_Bullet->enemybullet_.x < 40) {
			E_Bullet->enemy_isShot = false;
			E_Bullet->enemybullet_.x = enemy_.x - 40;
			E_Bullet->enemybullet_.y = enemy_.y;
		}
	}
	if (enemy_hp == 0) {
		E_Bullet->enemy_isShot = false;
	}
}

void Enemy::Draw() {
	int ENEMY = Novice::LoadTexture("./Resource/enemy.png");

	//“G‚Ì•`‰æ
	Novice::DrawEllipse(enemy_.x, enemy_.y,
		enemy_.radius, enemy_.radius, 0.0f, 0x00, kFillModeSolid);
	Novice::DrawSprite(enemy_.x - 40, enemy_.y - 25, ENEMY, 1, 1, 0.0f, WHITE);
}

void Enemy::OnCollision() {
	enemy_hp -= 1;
}