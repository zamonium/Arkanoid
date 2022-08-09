#include "Rod.h"

// Set the rod for a new game
void Rod::NewGame()
{
	SetX(ROD_X);
	SetY(ROD_Y);
	SetWidth(ROD_WIDTH);
	SetHeight(ROD_HEIGHT);
	m_fDir = 0.0f;
}

void Rod::Update()
{
	// Update rod position if it is moving and it can move
	if(m_fDir != 0 && CanMove(m_fDir))
		SetX(GetX() + m_fDir * m_fVel * DT);
}

void Rod::Render() const
{
	GLfloat x = GetX();
	GLfloat y = GetY();
	GLfloat width = GetWidth();
	GLfloat height = GetHeight();

	// Render the grey rod
	glBegin(GL_QUADS);
	glColor3f(0.5f, 0.5f, 0.5f);
	glVertex2f(x, y);
	glVertex2f(x + width, y);
	glVertex2f(x + width, y + height);
	glVertex2f(x, y + height);
	glEnd();

	// Render the bounds of the rod
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 0.0f, 0.0f); // Black
	glVertex2f(x, y);
	glVertex2f(x + width, y);
	glVertex2f(x + width, y + height);
	glVertex2f(x, y + height);
	glEnd();
}

// Change the X direction
void Rod::ChangeDirection(GLfloat direction)
{
	m_fDir = direction;
}

// Check if the rod can move in the direction parameter
bool Rod::CanMove(GLfloat direction)
{
	if (direction == RIGHT_DIR && GetX() + GetWidth() < RIGHT_BOUND)
		return true;
	
	if (direction == LEFT_DIR && GetX() > LEFT_BOUND)
		return true;

	return false; // Out of lateral bounds
}

GLfloat Rod::GetDirection()
{
	return m_fDir;
}
