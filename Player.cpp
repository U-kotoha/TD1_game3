#include <Novice.h>
#include <Player.h>

Player* player = new Player(600, 500, 20, 5);

Player::Player(int x, int y, int radius, int speed) {
	this->player_.x = 600;
	this->player_.y = 500;
	this->player_.radius = 80;
	this->player_.speed = 5;
}

void Player::Move(char* keys) {
	player->player_.speed = 5;

	if (keys[DIK_W]) {
		player->player_.y -= player->player_.speed;
	};
	if (keys[DIK_S]) {
		player->player_.y += player->player_.speed;
	};
	if (keys[DIK_A]) {
		player->player_.x -= player->player_.speed;
	};
	if (keys[DIK_D]) {
		player->player_.x += player->player_.speed;
	};
}

void Player::Draw() {
	Novice::DrawEllipse(player->player_.x, player->player_.y, player->player_.radius, player->player_.radius, 0.0f, WHITE, kFillModeSolid);
}