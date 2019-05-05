#pragma once

#include "RectF.h"

class Brick {
public:
	Brick() = default;
	Brick(Vec2 Position, float width, float height, Color c);
	void Draw(Graphics& gfx);
	bool DoBallCollision(Ball& ball, Graphics& gfx);
	bool IsDestroyed() const;

private:
	RectF shape;
	bool destroyed = false;
	static constexpr int borderWidth = 1;
	static constexpr int borderHeight = 1;
	Color borderColor = Colors::Black;
};