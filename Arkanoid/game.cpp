#include "game.h"

// Definition for the texture library STB image
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

// Game destructor
Game::~Game()
{
	if (m_oBall)
	{
		delete m_oBall;
		m_oBall = 0;
	}

	if (m_oRod)
	{
		delete m_oRod;
		m_oRod = 0;
	}

	if (m_oWall)
	{
		delete m_oWall;
		m_oWall = 0;
	}
}

// Delete the current active texture
void Game::DeleteTexture() 
{
	if (m_TextureBrick != 0)
	{
		glDeleteTextures(1, &m_TextureBrick);
		return;
	}
	if (m_TextureLose != 0)
	{
		glDeleteTextures(1, &m_TextureLose);
		return;
	}
	if (m_TextureWin != 0)
	{
		glDeleteTextures(1, &m_TextureWin);
		return;
	}
	if (m_TextureMain != 0)
	{
		glDeleteTextures(1, &m_TextureMain);
		return;
	}
}

void Game::Init()
{
	// Create objects
	m_oBall = new Ball();
	m_oRod = new Rod();
	m_oWall = new Wall();

	// Init rendering 
	glewInit();
	glViewport(0, 0, 480, 480);

	glClearColor(0.0, 0, 1.0, 1.0);

	// Set the main texture for the first start
	TextureMain();
}

void Game::NewGame()
{
	// Init objects for a new game
	m_bBallMoving = true;
	m_bRodMoving = false;
	m_bPlaying = true;
	m_bYouLose = false;

	// Set ball and rod as a new game
	m_oBall->NewGame();
	m_oRod->NewGame();

	// Delete the active texture
	DeleteTexture();

	// Create and bind the texture for the bricks
	TextureBrick();

	// Init and set the wall for a new game
	m_oWall->Init();
	m_oWall->NewGame();
}

void Game::Update()
{
	// Check if you lose
	CheckDeath();

	// Check Collisions
	CheckCollisions();

	// If the ball is still in a position good for the rod then update the rod
	if (!m_bYouLose)
		m_oRod->Update();

	// Update the ball
	m_oBall->Update();
}

// Render function calls the objects render
void Game::Render() 
{
	glClear(GL_COLOR_BUFFER_BIT);
	
	m_oRod->Render();
	m_oBall->Render();
	m_oWall->Render();

	glFlush();
}

// Render function that visualize the screens textures for main, you lose, you win
void Game::RenderImages()
{
	// Choose the correct texture to load and the render it
  	if (m_bFirstDrawCall)
	{
		DeleteTexture();

		if (m_bYouLose)
			TextureLose();
		else
			TextureWin();

		m_bFirstDrawCall = false;
	}
	
	glClear(GL_COLOR_BUFFER_BIT);
	
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_QUADS);
	glColor3f(1.0f, 1.0f, 1.0f);
	glTexCoord2f(0, 0); glVertex2f(-1.0f, 1.0f);
	glTexCoord2f(1, 0); glVertex2f(1.0f, 1.0f);
	glTexCoord2f(1, 1); glVertex2f(1.0f, -1.0f);
	glTexCoord2f(0, 1); glVertex2f(-1.0f, -1.0f);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glFlush();
}

void Game::ChangeRodDirection(GLfloat direction)
{
	m_oRod->ChangeDirection(direction);
}

// Return true if the position of the rod is between the lateral bounds considering the direction parameter
bool Game::CanRodMove(bool direction)
{
	return m_oRod->CanMove( (direction) ? 1 : -1);
}

bool Game::IsBallMoving()
{
	return m_bBallMoving;
}

bool Game::IsAlive()
{
	return m_bPlaying;
}

// Load and bind the texture for the bricks
void Game::TextureBrick()
{
	int w, h, comp;
	std::string filename = "Texture/brickTexture.png";
	unsigned char* image = stbi_load(filename.c_str(), &w, &h, &comp, 3);

	// Failed to load texture Brick 
	assert(image != nullptr);

	glGenTextures(1, &m_TextureBrick);

	glBindTexture(GL_TEXTURE_2D, m_TextureBrick);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

	glBindTexture(GL_TEXTURE_2D, m_TextureBrick);

	stbi_image_free(image);

}

// Load and bind the texture for the main screen
void Game::TextureMain()
{
	int w, h, comp;
	std::string filename = "Texture/arkanoid.png";
	unsigned char* image = stbi_load(filename.c_str(), &w, &h, &comp, 3);

	// Failed to load texture for main screen
	assert(image != nullptr);

	glGenTextures(1, &m_TextureMain);

	glBindTexture(GL_TEXTURE_2D, m_TextureMain);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

	glBindTexture(GL_TEXTURE_2D, m_TextureMain);

	stbi_image_free(image);
}

// Load and bind the texture for the you win screen
void Game::TextureWin()
{
	int w, h, comp;
	std::string filename = "Texture/win.png";
	unsigned char* image = stbi_load(filename.c_str(), &w, &h, &comp, 3);

	// Failed to load texture for win screen
	assert(image != nullptr);

	glGenTextures(1, &m_TextureWin);

	glBindTexture(GL_TEXTURE_2D, m_TextureWin);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

	glBindTexture(GL_TEXTURE_2D, m_TextureWin);

	stbi_image_free(image);
}

// Load and bind the texture for the you lose screen
void Game::TextureLose()
{
	int w, h, comp;
	std::string filename = "Texture/lose.png";
	unsigned char* image = stbi_load(filename.c_str(), &w, &h, &comp, 3);

	// Failed to load texture for lose screen
	assert(image != nullptr);

	glGenTextures(1, &m_TextureLose);

	glBindTexture(GL_TEXTURE_2D, m_TextureLose);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

	glBindTexture(GL_TEXTURE_2D, m_TextureLose);

	stbi_image_free(image);
}

// If the ball is colliding with the lower bound then you lose
void Game::CheckDeath()
{
	if (m_oBall->GetY() + BALL_RADIUS <= LOWER_BOUND)
	{
		m_bPlaying = false;
		m_bYouLose = true;
		m_bFirstDrawCall = true;
	}
}

void Game::CheckCollisions()
{
	if (m_bYouLose)
		return;

	CheckCollisionBounds();

	// if the ball is colliding with the rod i don't need to check the wall collisions
	if (!CheckCollisionRod())
		CheckCollisionWall();
}

// Check the collision with the upper and laterals bounds
void Game::CheckCollisionBounds()
{
	GLfloat xBall = m_oBall->GetX();
	GLfloat yBall = m_oBall->GetY();

	// Upper bound
	if (yBall + BALL_RADIUS >= UPPER_BOUND)
	{
		m_oBall->SetY(UPPER_BOUND - BALL_RADIUS);
		m_oBall->ChangeDirection(false);
	}

	// Right bound 
	if (xBall + BALL_RADIUS >= RIGHT_BOUND)
	{
		m_oBall->SetX(RIGHT_BOUND - BALL_RADIUS);
		m_oBall->ChangeDirection(true);
	}
	// Left bound
	else if (xBall - BALL_RADIUS <= LEFT_BOUND)
	{
		m_oBall->SetX(LEFT_BOUND + BALL_RADIUS);
		m_oBall->ChangeDirection(true);
	}
}

// Get the reflection value of the ball colliding with the rod
GLfloat Game::GetReflection(GLfloat bump)
{
	if (bump < 0) {
		bump = 0;
	}
	else if (bump > ROD_WIDTH) {
		bump = ROD_WIDTH;
	}

	// Everything to the left of the center of the rod is reflected to the left and vice versa
	bump -= ROD_WIDTH / 2.0f;

	// Scale the reflection, making it fall in the range -MAX_BALL_DIR to MAX_BALL_DIR
	return MAX_BALL_DIR * bump / (ROD_WIDTH / 2.0f);
}


// Check the collision with the rod
bool Game::CheckCollisionRod()
{
	GLfloat xBall = m_oBall->GetX();
	GLfloat yBall = m_oBall->GetY();

	GLfloat xRod = m_oRod->GetX();
	GLfloat yRod = m_oRod->GetY();
	
	if ((xBall + BALL_RADIUS) >= xRod && (xBall - BALL_RADIUS) <= xRod + ROD_WIDTH && yBall - BALL_RADIUS <= yRod + ROD_HEIGHT)
	{
		if (yBall - BALL_RADIUS >= yRod + ROD_HEIGHT - ROD_HEIGHT / 3) // approximation
		{
			m_oBall->SetY(m_oRod->GetY() + m_oRod->GetHeight() + BALL_RADIUS);
			m_oBall->SetDirection(GetReflection(m_oBall->GetX() - m_oRod->GetX()), 1);
		}
		else 
		{
			if (yBall + BALL_RADIUS >= yRod)
			{
				if (m_oBall->GetDirX())// If direction right
				{
					if (xBall < xRod && m_oRod->GetDirection() != LEFT_DIR)
					{
						m_oBall->SetX(xRod - BALL_RADIUS);
					}

					
				}
				else
				{
					if (xBall > xRod && m_oRod->GetDirection() != RIGHT_DIR)
					{
						m_oBall->SetX(xRod + ROD_WIDTH + BALL_RADIUS);
					}
				}

				m_oBall->ChangeDirection(true);
				
			}

			m_bYouLose = true;
		}

		return true;
	}

	return false;
}

// If the ball is colliding with the wall then check the collisions of the bricks
void Game::CheckCollisionWall()
{
	if (m_oBall->GetY() + BALL_RADIUS >= m_oWall->GetY() || m_oBall->GetY() - BALL_RADIUS <= m_oWall->GetY() + WALL_HEIGHT)
		CheckCollisionBrick();
}

// To detect the ball collision with the bricks i use the Minkowski sum
void Game::CheckCollisionBrick()
{
	for (int i = 0; i < TOTAL_BRICKS; ++i)
	{
		Brick* brick = m_oWall->GetBrick(i);
		if (brick->IsActive())
		{
			// Center of the ball
			GLfloat xBrick = brick->GetX();
			GLfloat yBrick = brick->GetY();

			float w = 0.5f * (2 * BALL_RADIUS + WALL_WIDTH);
			float h = 0.5f * (2 * BALL_RADIUS + WALL_HEIGHT);
			float dx = (m_oBall->GetX()) - (xBrick + 0.5f*WALL_WIDTH);
			float dy = (m_oBall->GetY()) - (yBrick + 0.5f*WALL_HEIGHT);

			if (abs(dx) <= w && abs(dy) <= h) 
			{
				// Collision detected
				brick->DecrementLife();
				if (brick->GetLife() == 0)
				{
					brick->SetActive(false);
					m_oWall->BrickHit();
				}
				
				if (m_oWall->GetActiveBricks() == 0)
				{
					// You win
					m_bPlaying = false; 
					m_bFirstDrawCall = true;
				}

				float wy = w * dy;
				float hx = h * dx;

				if (wy > hx) 
				{
					if (wy > -hx) 
					{
						// Top
						BallBrickResponse(3);
						m_oBall->SetY(yBrick + BRICK_HEIGHT + BALL_RADIUS);
					}
					else 
					{
						// Left
						BallBrickResponse(0);
						m_oBall->SetX(xBrick - BALL_RADIUS);
					}
				}
				else 
				{
					if (wy > -hx) 
					{
						// Right
						BallBrickResponse(2);
						m_oBall->SetX(xBrick + BRICK_WIDTH + BALL_RADIUS);
					}
					else 
					{
						// Bottom
						BallBrickResponse(1);
						m_oBall->SetY(yBrick - BALL_RADIUS);
					}
				}
				return;
			}
		}
	}
}

void Game::BallBrickResponse(int dir) 
{
	// Direction factors
	int mulx = 1;
	int muly = 1;

	if (m_oBall->GetDirX()) 
	{
		// Ball is moving in the positive x direction
		if (m_oBall->GetDirY()) 
		{
			// Ball is moving in the positive y direction
			// +1 +1
			if (dir == 0 || dir == 3)
			{
				m_oBall->ChangeDirection(true);
			}
			else 
			{
				m_oBall->ChangeDirection(false);
			}
		}
		else if (!m_oBall->GetDirY()) 
		{
			// Ball is moving in the negative y direction
			// +1 -1
			if (dir == 0 || dir == 1)
			{
				m_oBall->ChangeDirection(true);
			}
			else 
			{
				m_oBall->ChangeDirection(false);
			}
		}
	}
	else if (!m_oBall->GetDirX()) 
	{
		// Ball is moving in the negative x direction
		if (m_oBall->GetDirY()) 
		{
			// Ball is moving in the positive y direction
			// -1 +1
			if (dir == 2 || dir == 3)
			{
				m_oBall->ChangeDirection(true);
			}
			else 
			{
				m_oBall->ChangeDirection(false);
			}
		}
		else if (!m_oBall->GetDirY()) 
		{
			// Ball is moving in the negative y direction
			// -1 -1
			if (dir == 1 || dir == 2)
			{
				m_oBall->ChangeDirection(true);
			}
			else 
			{
				m_oBall->ChangeDirection(false);
			}
		}
	}
}

