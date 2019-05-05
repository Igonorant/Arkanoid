/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "SpriteCodex.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	ball(Vec2(250.0f,400.0f), Vec2(300.0f,300.0f)),
	pad(Vec2(300.0f,500.0f),120.0f,20.0f,550.0f)
{

	// bricks initialization
	int n = 0;
	for (int i = 0; i < yBrickNumber; i++) {

		// bricks color initilization
		switch (i % 5) {
		case 0:
			bricksColors[i] = Colors::Blue;
			break;
		case 1:
			bricksColors[i] = Colors::Magenta;
			break;
		case 2:
			bricksColors[i] = Colors::Green;
			break;
		case 3:
			bricksColors[i] = Colors::Gray;
			break;
		case 4:
			bricksColors[i] = Colors::Yellow;
			break;
		}

		for (int j = 0; j < xBrickNumber; j++) {
			bricks[n] = Brick(Vec2(j*brickWidth+xBrickStart,i*brickHeight+yBrickStart), brickWidth, brickHeight, bricksColors[i]);
			n++;
		}
	}
}

void Game::Go()
{
	gfx.BeginFrame();	
	float elapsedTime = FrameTime.Mark();
	while (elapsedTime > 0.0f)
	{
		const float dt = std::min(0.0025f, elapsedTime);
		UpdateModel(dt);
		elapsedTime -= dt;
	}
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel(float dt)
{
	bool death = false;
	if (lives >= 0) {

		// update the ball
		ball.Update(dt);
		pad.Update(dt, wnd);

		// check and execute collisions
		pad.DoWallCollision(gfx);
		death = ball.DoWallCollision(gfx);
		pad.DoBallCollision(ball, gfx);
		for (int i = 0; i < brickNumber; i++) {
			if (!bricks[i].IsDestroyed()) {
				bricks[i].DoBallCollision(ball, gfx);
			}
		}

		// check if the ball touched the bottom wall
		if (death) {
			lives--;
			ball.Respawn();
		}
	
	}

}

void Game::ComposeFrame()
{

	pad.Draw(gfx);
	ball.Draw(gfx);	
	for (int i = 0; i < brickNumber; i++) {
		if (!bricks[i].IsDestroyed()) {
			bricks[i].Draw(gfx);
		}
	}
	for (int i = 0; i < lives; i++) {
		SpriteCodex::DrawBall(Vec2( (1 + i) * 30.0f, gfx.ScreenHeight - 30.0f), gfx);
	}

}
