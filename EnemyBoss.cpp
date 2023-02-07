#include <Novice.h>
#include <EnemyBoss.h>

//•Ï”éŒ¾
bool enemyjump = false;
float enemyyadd = 0.0f;
float enemydown = 0.0f;
int enemypoint = 0;
int countdown = 0;

EnemyBoss::EnemyBoss() {
	//‰Šú‰»
	enemyboss_hp = 10;
	enemyboss_.x = 800;
	enemyboss_.y = 495;
	enemyboss_.radius = 50;
	enemyboss_.speed = 4;

	E_Bullet = new EnemyBullet;
}

EnemyBoss::~EnemyBoss() {
	//ƒ|ƒCƒ“ƒ^íœ
	delete E_Bullet;
}

void EnemyBoss::Update() {
	//“G‚ÌUŒ‚
	if (enemyboss_hp != 0) {
		if (E_Bullet->enemy_isShot == false) {
			E_Bullet->enemy_isShot = true;
			E_Bullet->enemybullet_.x = enemyboss_.x - 40;
			E_Bullet->enemybullet_.y = enemyboss_.y;
		}
		if (E_Bullet->enemy_isShot == true) {
			E_Bullet->enemybullet_.x -= E_Bullet->enemybullet_.speed;
		}
		if (E_Bullet->enemybullet_.x < 40) {
			E_Bullet->enemy_isShot = false;
			E_Bullet->enemybullet_.x = enemyboss_.x - 40;
			E_Bullet->enemybullet_.y = enemyboss_.y;
		}
	}
	if (enemyboss_hp == 0) {
		E_Bullet->enemy_isShot = false;
	}

	//“G‚ÌƒWƒƒƒ“ƒv
	countdown++;
	if (countdown >= 30) {
		enemyjump = true;
	}
	if (enemyjump == true) {
		enemyyadd = -5.0f;
		enemydown = +5.0f;
	}
	if (enemyjump == true) {
		if (enemypoint == 0) {
			enemyboss_.y += enemyyadd;
		}
	}
	if (enemyjump == true) {
		if (enemyboss_.y <= 370) {
			enemypoint = 1;
		}
	}
	if (enemypoint == 1) {
		enemyboss_.y += enemydown;
	}
	if (enemyboss_.y == 495) {
		enemyjump = 0;
		enemypoint = 0;
	}
}

void EnemyBoss::Draw() {
	int ENEMYBOSS = Novice::LoadTexture("./Resource/enemyboss.png");
	Novice::DrawSprite(enemyboss_.x - 65, enemyboss_.y - 65, ENEMYBOSS, 1, 1, 0.0f, WHITE);
	//Novice::DrawEllipse(enemyboss_.x, enemyboss_.y, enemyboss_.radius, enemyboss_.radius, 0.0f, GREEN, kFillModeSolid);
}

void EnemyBoss::OnCollision() {
	enemyboss_hp -= 1;
}