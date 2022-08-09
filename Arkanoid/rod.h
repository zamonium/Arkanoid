#pragma once

#include "rectangle.h"

#define ROD_X -0.2f
#define ROD_Y -0.8f
#define ROD_WIDTH 0.4f
#define ROD_HEIGHT 0.1f
#define ROD_VELOCITY 2.0f
#define RIGHT_DIR 1
#define LEFT_DIR -1

class Rod : public Rectangle
{
public:
	Rod() : Rectangle(), m_fDir(0), m_fVel(ROD_VELOCITY) {};
	~Rod() {};

	void NewGame();
	void Update();
	void Render() const;

	void ChangeDirection(GLfloat);
	bool CanMove(GLfloat);
	GLfloat GetDirection();

private:
	GLfloat m_fDir;
	GLfloat m_fVel;
};
