#include "Paddle.h"

Paddle::Paddle(Vec2 startPosition, float width, float height, float velocity)
{
	padVelocity = velocity;
	shape = RectF(startPosition, width, height, mainColor);
}

void Paddle::Update(float dt, MainWindow& wnd)
{
	// keyboard input to speedup the pad
	float currentVelocity;
	if (wnd.kbd.KeyIsPressed(VK_LEFT)) {
		currentVelocity = -padVelocity;
	}
	else if (wnd.kbd.KeyIsPressed(VK_RIGHT)) {
		currentVelocity = padVelocity;
	}
	else {
		currentVelocity = 0.0f;
	}
	shape.UpdateX(currentVelocity * dt);
}

void Paddle::Draw(Graphics& gfx)
{
	shape.DrawWithBorder(gfx, borderWidth, 0, borderColor);
}

bool Paddle::DoBallCollision(Ball& ball, Graphics& gfx)
{

	return shape.DoBallCollision(ball,gfx);

}

void Paddle::DoWallCollision(Graphics& gfx)
{
	// left corner
	if (shape.GetWallX0() < 0) {
		shape.SetX(0.0f);
	}
	// right corner
	if (shape.GetWallX1() >= gfx.ScreenWidth) {
		shape.SetX(gfx.ScreenWidth - shape.GetWidth()- 1);
	}
}

