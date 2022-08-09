#pragma once

#include "gameobject.h"

class Circle : public GameObject
{
public:
	Circle() : GameObject(), m_fX(0), m_fY(0), m_fRadius(0) {}
	virtual ~Circle() {};

	virtual void NewGame() = 0;
	virtual void Update() = 0;
	virtual void Render() const = 0;

	GLfloat GetX() const { return m_fX; }
	GLfloat GetY() const { return m_fY; }
	GLfloat GetRadius() const { return m_fRadius; }

	void SetX(GLfloat value) { m_fX = value; }
	void SetY(GLfloat value) { m_fY = value; }
	void SetRadius(GLfloat value) { m_fRadius = value; }

private:
	// X and Y are the center of the circle
	GLfloat m_fX, m_fY;
	GLfloat m_fRadius;
	
};