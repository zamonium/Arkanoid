#pragma once

#include "rectangle.h"

#define BRICK_WIDTH 0.2f
#define BRICK_HEIGHT 0.1f

enum Colors // RGB
{
	Null = 0,
	Red = 1,     // 1, 0, 0
	Green = 2,   // 0, 1, 0
	Magenta = 3, // 1, 0, 1
	Yellow = 4   // 1, 1, 0
};

class Brick : public Rectangle
{
public:
	Brick() : Rectangle(), m_bIsActive(false), m_eColor(), m_iLife(0){};
	virtual ~Brick() {};

	void NewGame();
	void SetPosition(GLfloat, GLfloat);
	void Update() {};
	void Render() const;

	bool IsActive();
	void SetActive(bool);

	void SetColor(Colors);
	Colors GetColor();

	virtual bool IsTexture();
	virtual void SetTexture(GLuint) {};

	void DecrementLife();
	int GetLife();
	void SetLife(int);

protected:
	GLfloat GetColorR(Colors) const;
	GLfloat GetColorG(Colors) const;
	GLfloat GetColorB(Colors) const;

	bool m_bIsActive;
	Colors m_eColor;
	int m_iLife;
};
