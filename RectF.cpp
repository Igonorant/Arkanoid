#include "RectF.h"

RectF::RectF(Vec2 topLeft_in, Vec2 bottomRight_in, Color c_in)
{
	topLeft = topLeft_in;
	bottomRight = bottomRight_in;
	c = c_in;
}

RectF::RectF(Vec2 topLeft_in, float width, float height, Color c_in)
	:
	RectF(topLeft_in, Vec2(topLeft_in.x + width, topLeft_in.y + height), c_in)
{
	
}

void RectF::Draw(Graphics& gfx)
{
	gfx.DrawRect(int(topLeft.x), int(topLeft.y), int(bottomRight.x), int(bottomRight.y),c);
}

void RectF::DrawWithBorder(Graphics& gfx, int upBorderWidth, int sideBorderWidth, Color borderColor)
{
	Vec2 newTopLeft = topLeft + Vec2(float(upBorderWidth), float(sideBorderWidth));
	Vec2 newBottomRight = bottomRight - Vec2(float(upBorderWidth), float(sideBorderWidth));

	gfx.DrawRect(int(topLeft.x), int(topLeft.y), int(bottomRight.x), int(bottomRight.y), borderColor);
	gfx.DrawRect(int(newTopLeft.x), int(newTopLeft.y), int(newBottomRight.x), int(newBottomRight.y), c);

}

float RectF::GetWidth() const
{
	return bottomRight.x - topLeft.x;
}

float RectF::GetWallX0() const
{
	return topLeft.x;
}

float RectF::GetWallX1() const
{
	return bottomRight.x;
}

float RectF::GetWallY0() const
{
	return topLeft.y;
}

float RectF::GetWallY1() const
{
	return bottomRight.y;
}

void RectF::UpdateX(float x)
{
	topLeft.x += x;
	bottomRight.x += x;
}

void RectF::SetX(float x)
{
	float width = GetWidth();
	topLeft.x = x;
	bottomRight.x = x + width;
}

bool RectF::DoBallCollision(Ball& ball, Graphics& gfx)
{
	// Quadrants
	//	_5__|____1____|__6_
	//      |         |
	//	 3  |  shape  |  4
	//	____|_________|____
	//	 7  |    2    |  8
	
	Vec2 center = ball.GetCenter();
	if (center.x >= GetWallX0() && center.x <= GetWallX1() && center.y <= GetWallY0() && center.y <= GetWallY1()) { // 1st quadrant
		float distance = ball.DistanceFromCenterY(GetWallY0());
		if ( distance <= ball.GetRadius()) { // check distance less than radius
			ball.ReboundY(-distance);
			ball.DoWallCollision(gfx);
			return true;
		 }
	}
	if (center.x >= GetWallX0() && center.x <= GetWallX1() && center.y >= GetWallY0() && center.y >= GetWallY1()) { // 2nd quadrant
		float distance = -ball.DistanceFromCenterY(GetWallY1());
		if ( distance <= ball.GetRadius()) { // check distance less than radius
			ball.ReboundY(distance);
			ball.DoWallCollision(gfx);
			return true;
		}
	}
	if (center.x <= GetWallX0() && center.x <= GetWallX1() && center.y >= GetWallY0() && center.y <= GetWallY1()) { // 3rd quadrant
		float distance = ball.DistanceFromCenterX(GetWallX0());
		if ( distance <= ball.GetRadius()) { // check distance less than radius
			ball.ReboundX(-distance);
			ball.DoWallCollision(gfx);
			return true;
		}
	}
	if (center.x >= GetWallX0() && center.x >= GetWallX1() && center.y >= GetWallY0() && center.y <= GetWallY1()) { // 4th quadrant
		float distance = -ball.DistanceFromCenterX(GetWallX1());
		if ( distance <= ball.GetRadius()) { // check distance less than radius
			ball.ReboundX(distance);
			ball.DoWallCollision(gfx);
			return true;
		}
	}
	if (center.x <= GetWallX0() && center.y <= GetWallY0()) { // 5th quadrant
		float distance = ball.DistanceSqr(topLeft);
		if (distance <= ball.GetRadiusSqr()) { // check distance less than radius
			ball.ReboundXY((ball.GetCenter()-topLeft));
			ball.DoWallCollision(gfx);
			return true;
		}
	}
	if (center.x >= GetWallX1() && center.y <= GetWallY0()) { // 6th quadrant
		float distance = ball.DistanceSqr(Vec2(GetWallX1(), GetWallY0()));
		if (distance <= ball.GetRadiusSqr()) { // check distance less than radius
			ball.ReboundXY((ball.GetCenter() - Vec2(GetWallX1(), GetWallY0())));
			ball.DoWallCollision(gfx);
			return true;
		}
	}
	if (center.x <= GetWallX0() && center.y >= GetWallY1()) { // 7th quadrant
		float distance = ball.DistanceSqr(Vec2(GetWallX0(), GetWallY1()));
		if (distance <= ball.GetRadiusSqr()) { // check distance less than radius
			ball.ReboundXY((ball.GetCenter() - Vec2(GetWallX0(), GetWallY1())));
			ball.DoWallCollision(gfx);
			return true;
		}
	}
	if (center.x >= GetWallX1() && center.y >= GetWallY1()) { // 8th quadrant
		float distance = ball.DistanceSqr(bottomRight);
		if (distance <= ball.GetRadiusSqr()) { // check distance less than radius
			ball.ReboundXY((ball.GetCenter() - bottomRight));
			ball.DoWallCollision(gfx);
			return true;
		}
	}


	return false;
}
