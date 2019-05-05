#pragma once

#include "Vec2.h"
#include "Graphics.h"
#include "Colors.h"
#include "Ball.h"

class RectF {
public:
	RectF() = default;
	RectF(Vec2 topLeft_in, Vec2 bottomRight_in, Color c_in);
	RectF(Vec2 topLeft_in, float width, float height, Color c_in);
	void Draw(Graphics& gfx);
	void DrawWithBorder(Graphics& gfx, int upBorderWidth, int sideBorderWidth, Color borderColor);
	float GetWidth() const;
	float GetWallX0() const;
	float GetWallX1() const;
	float GetWallY0() const;
	float GetWallY1() const;
	void UpdateX(float x);
	void SetX(float x);
	bool DoBallCollision(Ball& ball, Graphics& gfx);

private:
	Vec2 topLeft;
	Vec2 bottomRight;
	Color c;
};