#pragma once

//�v���C���[�\����
typedef struct Player_ {
	int x;
	int y;
	int radius;
	int speed;
};

//�e�̍\����
typedef struct Bullet_ {
	int x;
	int y;
	int radius;
	int speed;
	int isShot;
};
