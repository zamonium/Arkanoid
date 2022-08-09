#include "Ball.h"

// Set the ball for a new game
void Ball::NewGame() 
{
	SetX(BALL_X);
	SetY(BALL_Y + EPSILON); // little bit more than the rod so i avoid the first collision
	SetRadius(BALL_RADIUS);
	m_fDirX = MAX_BALL_DIR;
	m_fDirY = MAX_BALL_DIR;
}

void Ball::Update() 
{
	// Update the position of the ball
	SetX(GetX() + m_fDirX * m_fVel * DT);
	SetY(GetY() + m_fDirY * m_fVel * DT);
}

void Ball::SetDirection(GLfloat dirX, GLfloat dirY)
{
	m_fDirX = dirX;
	m_fDirY = dirY;
}

// Return true if the direction is right, false if left
bool Ball::GetDirX()
{
	if (m_fDirX > 0.0f)
		return true;
	if (m_fDirX < 0.0f)
		return false;
}

// Return true if the direction is up, false if down

bool Ball::GetDirY()
{
	if (m_fDirY == 1.0f)
		return true;
	if (m_fDirY == -1.0f)
		return false;
}

// true = invert X direction, false = invert Y direction
void Ball::ChangeDirection(bool dir)
{
	if (dir)
		m_fDirX *= -1.0f;
	else
		m_fDirY *= -1.0f;
}

void Ball::Render() const
{
	GLfloat x = GetX();
	GLfloat y = GetY();

	// Render the filled ball
	int i;
	int triangleAmount = 20; //# of triangles used to draw circle

	GLfloat twicePi = 2.0f * GetPI();

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(x, y); // center of circle
	for (i = 0; i <= triangleAmount; i++) {
		glVertex2f(
			x + (BALL_RADIUS * cos(i *  twicePi / triangleAmount)),
			y + (BALL_RADIUS * sin(i * twicePi / triangleAmount))
		);
	}
	glEnd();

	// Render the circumference of the ball
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 0.0f, 0.0f);
	for (int i = 0; i < 50; i++)
	{
	float theta = 2.0f * 3.1415926f * float(i) / float(50);//get the current angle

	float dx = BALL_RADIUS * cosf(theta);//calculate the x component
	float dy = BALL_RADIUS * sinf(theta);//calculate the y component

	glVertex2f(dx + x, dy + y);//output vertex

	}
	glEnd();

}
