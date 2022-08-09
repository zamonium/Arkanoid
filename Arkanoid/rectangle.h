#pragma once

#include "gameobject.h"

class Rectangle : public GameObject 
{
public:
	Rectangle() : GameObject(), m_fX(0), m_fY(0), m_fWidth(0), m_fHeight(0) {}
	virtual ~Rectangle() {};

	virtual void NewGame() = 0;
	virtual void Update() = 0;
	virtual void Render() const = 0;

	GLfloat GetX() const { return m_fX; }
	GLfloat GetY() const { return m_fY; }
	GLfloat GetWidth() const { return m_fWidth; }
	GLfloat GetHeight() const { return m_fHeight; }

	void SetX(GLfloat value) { m_fX = value; }
	void SetY(GLfloat value) { m_fY = value; }
	void SetWidth(GLfloat value) { m_fWidth = value; }
	void SetHeight(GLfloat value) { m_fHeight = value; }

private:
	// X and Y are the bottom-left vertex of the rectangle 
	GLfloat m_fX, m_fY;
	GLfloat m_fWidth, m_fHeight;
};