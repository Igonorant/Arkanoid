#pragma once

#include "RectF.h"
#include "Ball.h"
#include "MainWindow.h"


class Paddle {
public:
	Paddle(Vec2 startPosition, float width, float height, float velocity);
	void Update(float dt, MainWindow& wnd);
	void Draw(Graphics& gfx);
	bool DoBallCollision(Ball& ball, Graphics& gfx);
	void DoWallCollision(Graphics& gfx);
	void SetVelocity(float velocity);


private:
	RectF shape;
	Color mainColor = Colors::Magenta;
	Color borderColor = Colors::Green;
	const int borderWidth = 10;
	float padVelocity;

};