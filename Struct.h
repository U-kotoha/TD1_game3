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

//�}�E�X
typedef struct Mouse_ {
	int posX; //�}�E�X��X���W
	int posY; //�}�E�X��Y���W
	int clickCount; //�J�E���g
	bool isLeftClick; //���N���b�N����
	bool isRightClick; //�E�N���b�N����
};