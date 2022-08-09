#pragma once

#include <math.h>

#include <iostream>
#include<GL/glew.h>
#include <assert.h>

#include "ball.h"
#include "Rod.h"
#include "Wall.h"

#define DT 1.0/30

class Game
{
public:
	Game() : m_oBall(0), m_oRod(0), m_oWall(0), m_bBallMoving(false), m_bRodMoving(false), 
		m_bPlaying(false), m_bYouLose(false), m_bFirstDrawCall(false), 
		m_TextureBrick(0), m_TextureMain(0), m_TextureLose(0), m_TextureWin(0) {};
	~Game();

	void Init();
	void NewGame();
	void Update();
	void Render();
	void RenderImages();

	void ChangeRodDirection(GLfloat);
	bool CanRodMove(bool);
	bool IsBallMoving();
	bool IsAlive();

private:
	void TextureMain();
	void TextureBrick();
	void TextureWin();
	void TextureLose();
	void DeleteTexture();

	void CheckDeath();
	void CheckCollisions();
	void CheckCollisionBounds();
	bool CheckCollisionRod();
	void CheckCollisionWall();
	void CheckCollisionBrick();
	GLfloat GetReflection(GLfloat bump);
	void BallBrickResponse(int);

	Ball* m_oBall;
	Rod* m_oRod;
	Wall* m_oWall;
	bool m_bBallMoving;
	bool m_bRodMoving;
	bool m_bPlaying;
	bool m_bYouLose;
	bool m_bFirstDrawCall;

	GLuint m_TextureBrick;
	GLuint m_TextureMain;
	GLuint m_TextureWin;
	GLuint m_TextureLose;
};

