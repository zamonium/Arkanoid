#include "brick.h"

// Set the brick for a new game
void Brick::NewGame()
{
	SetWidth(BRICK_WIDTH);
	SetHeight(BRICK_HEIGHT);

	m_bIsActive = true;
	if(IsTexture())
		m_iLife = 2;
	else
		m_iLife = 1;
}

void Brick::SetPosition(GLfloat x, GLfloat y)
{
	SetX(x);
	SetY(y);
}

void Brick::Render() const
{
	GLfloat x = GetX();
	GLfloat y = GetY();
	GLfloat width = GetWidth();
	GLfloat height = GetHeight();

	// Render the colored brick
	glBegin(GL_QUADS);
	glColor3f(GetColorR(m_eColor), GetColorG(m_eColor), GetColorB(m_eColor));
	glVertex2f(x, y);
	glVertex2f(x + width, y);
	glVertex2f(x + width, y + height);
	glVertex2f(x, y + height);
	glEnd();

	// Render the bounds of the brick
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 0.0f, 0.0f); // Black
	glVertex2f(x, y);
	glVertex2f(x + width, y);
	glVertex2f(x + width, y + height);
	glVertex2f(x, y + height);
	glEnd();
}

bool Brick::IsActive()
{
	return m_bIsActive;
}

void Brick::SetActive(bool value)
{
	m_bIsActive = value;
}

void Brick::SetColor(Colors newCol)
{
	m_eColor = newCol;
}

Colors Brick::GetColor()
{
	return m_eColor;
}

bool Brick::IsTexture()
{
	return false;
}

void Brick::DecrementLife()
{
	--m_iLife;
}

int Brick::GetLife()
{
	return m_iLife;
}

void Brick::SetLife(int newLife)
{
	m_iLife = newLife;
}

GLfloat Brick::GetColorR(Colors col) const
{
	if (col != Green)
		return 1.0f;
	else
		return 0.0f;
}

GLfloat Brick::GetColorG(Colors col) const
{
	if (col == Red || col == Magenta)
		return 0.0f;
	else
		return 1.0f;
}

GLfloat Brick::GetColorB(Colors col) const
{
	if (col != Magenta)
		return 0.0f;
	else
		return 1.0f;
}
