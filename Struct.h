#pragma once

//�}�E�X
typedef struct Mouse
{
	int posX; //�}�E�X��X���W
	int posY; //�}�E�X��Y���W
	int clickCount; //�J�E���g
	bool isLeftClick; //���N���b�N����
	bool isRightClick; //�E�N���b�N����
};

//�\����
typedef struct Player_ {
	int x;
	int y;
	int radius;
	int speed;
};

typedef struct Bullet_ {
	int x;
	int y;
	int radius;
	int speed;
	int isShot;
};