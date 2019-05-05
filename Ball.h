#pragma once

#include "Graphics.h"
#include "Vec2.h"
#include <cmath>

class Ball {
public:
	Ball(Vec2 StartCenter, Vec2 StartVelocity);
	void Draw(Graphics& gfx) const;
	void Update(float dt);
	bool DoWallCollision(Graphics& gfx);
	void ReboundX();
	void ReboundY();
	void ReboundX(float x);
	void ReboundY(float y);
	void ReboundXY(Vec2& distance);
	float DistanceSqr(Vec2& point);
	float Distance(Vec2& point);
	float DistanceFromCenterX(float x) const;
	float DistanceFromCenterY(float y) const;
	Vec2 GetCenter() const;
	float GetRadius() const;
	float GetRadiusSqr() const;
	void Respawn();

private:
	const float radius = 7.0f;
	Vec2 center;
	Vec2 vel;
	Vec2 centerRespawn;
};