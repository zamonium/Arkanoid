#pragma once

#include "circle.h"

#include <math.h>

#define BALL_X 0.0f
#define BALL_Y -0.65f
#define BALL_RADIUS 0.05f
#define BALL_VELOCITY 1.0f
#define MAX_BALL_DIR 0.8f
#define EPSILON 0.005f

class Ball : public Circle
{
public:
	Ball() : Circle(), m_fDirX(0), m_fDirY(0), m_fVel(BALL_VELOCITY) {};
	~Ball() {};

	void NewGame();
	void Update();
	void Render() const;
	
	void ChangeDirection(bool);
	void SetDirection(GLfloat, GLfloat);
	bool GetDirX();
	bool GetDirY();
	GLfloat GetPI() const { return PI; }

private:
	GLfloat m_fDirX, m_fDirY;
	GLfloat m_fVel;
	const double PI = atan(1.0) * 4;
};

