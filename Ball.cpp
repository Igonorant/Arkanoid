#include "Ball.h"
#include "SpriteCodex.h"

Ball::Ball(Vec2 StartCenter, Vec2 StartVelocity)
{
	center = StartCenter;
	vel = StartVelocity;
	centerRespawn = StartCenter;
}

void Ball::Draw(Graphics& gfx) const
{
	SpriteCodex::DrawBall(center, gfx);
}

void Ball::Update(float dt)
{
	center += vel * dt;
}

bool Ball::DoWallCollision(Graphics& gfx)
{
	// rebound left corner
	if (center.x - radius <= 0) {
		center.x -= 2 * (center.x - radius); // move the ball to inside the frame by the same amount it was out, simulating constant speed
		ReboundX();
		return false;
	}
	// rebound right corner
	if (center.x + radius >= gfx.ScreenWidth) {
		center.x -= 2 * (center.x + radius - gfx.ScreenWidth + 1); // move the ball to inside the frame by the same amount it was out, simulating constant speed
		ReboundX();
		return false;
	}
	// rebound upper corner
	if (center.y - radius <= 0) {
		center.y -= 2 * (center.y - radius); // move the ball to inside the frame by the same amount it was out, simulating constant speed
		ReboundY();
		return false;
	}
	// rebound bottom corner - or just die
	if (center.y + radius >= gfx.ScreenHeight) {
		center.y -= 2 * (center.y + radius - gfx.ScreenHeight + 1); // move the ball to inside the frame by the same amount it was out, simulating constant speed
		ReboundY();
		return true;
	}
	return false;
}

void Ball::ReboundX()
{
	vel.x = -vel.x;
}

void Ball::ReboundY()
{
	vel.y = -vel.y;
}

void Ball::ReboundX( float x)
{
	vel.x = -vel.x;
	center.x += x;
}

void Ball::ReboundY( float y)
{
	vel.y = -vel.y;
	center.y += y;
}

void Ball::ReboundXY(Vec2& distance)
{
	center += distance;
	ReboundX();
	ReboundY();
}

float Ball::DistanceSqr(Vec2& point)
{
	float x = center.x - point.x;
	float y = center.y - point.y;
	return (x * x + y * y);
}

float Ball::Distance(Vec2& point)
{
	return std::sqrt(DistanceSqr(point));
}

float Ball::DistanceFromCenterX(float x) const
{
	return x - center.x;
}
float Ball::DistanceFromCenterY(float y) const
{
	return y - center.y;
}

Vec2 Ball::GetCenter() const
{
	return center;
}

float Ball::GetRadius() const
{
	return radius;
}

float Ball::GetRadiusSqr() const
{
	return radius*radius;
}

void Ball::Respawn()
{
	center.y = centerRespawn.y;
}
