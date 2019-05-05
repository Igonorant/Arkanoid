#include "Brick.h"

Brick::Brick(Vec2 Position, float width, float height, Color c)
{
	shape = RectF(Position, width, height, c);
}

void Brick::Draw(Graphics& gfx)
{
	shape.DrawWithBorder(gfx, borderWidth, borderHeight, borderColor);
}

bool Brick::DoBallCollision(Ball& ball, Graphics& gfx)
{
	if (!destroyed && shape.DoBallCollision(ball, gfx)) {
		destroyed = true;
		return true;
	}
	return false;
}

bool Brick::IsDestroyed() const
{
	return destroyed;
}
