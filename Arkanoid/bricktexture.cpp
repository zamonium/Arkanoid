#include "BrickTexture.h"

void BrickTexture::Render() const
{
	GLfloat x = GetX();
	GLfloat y = GetY();
	GLfloat width = GetWidth();
	GLfloat height = GetHeight();

	// Render the brick texture
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0, 0); glVertex2f(x, y + height);
	glTexCoord2f(1, 0); glVertex2f(x + width, y + height);
	glTexCoord2f(1, 1); glVertex2f(x + width, y);
	glTexCoord2f(0, 1); glVertex2f(x, y);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	// Render the bounds of the brick
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 0.0f, 0.0f); // Black
	glVertex2f(x, y + height);
	glVertex2f(x + width, y + height);
	glVertex2f(x + width, y);
	glVertex2f(x, y);
	glEnd();
}

bool BrickTexture::IsTexture()
{
	return true;
}
