#pragma once
#include <Struct.h>

//�}�E�X�̃N���X
class Mouse {
public:

	Mouse_ mouse_;

public:

	Mouse();

	//�}�E�X����̊֐�
	void MouseOperation(Mouse& mouse);

	//�I����ʕ`��̊֐�
	void Select(float m, Mouse& mouse);

	//�Q�[���I�[�o�[
	void SpriteGameover(Mouse& mouse, char keys[]);

	//�Q�[���N���A
	void SpriteGameclear(Mouse& mouse, char keys[]);
};