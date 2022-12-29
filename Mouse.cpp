#include <Novice.h>
#include <Mouse.h>

Mouse::Mouse() {
	mouse_.posX = 0;
	mouse_.posY = 0;
	mouse_.clickCount = 0;
	mouse_.isLeftClick = false;
	mouse_.isRightClick = false;
}
float m = 0;

void Mouse::MouseOperation(Mouse& mouse) {

}

void Mouse::Select(float m, Mouse& mouse) {

}

void Mouse::SpriteGameover(Mouse& mouse, char keys[]) {

}

void Mouse::SpriteGameclear(Mouse& mouse, char keys[]) {

}
