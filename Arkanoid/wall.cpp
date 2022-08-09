#include "Wall.h"

Wall::~Wall()
{
	for(int i= TOTAL_BRICKS-1;i>=0;--i)
	{
		if (m_oBricks)
		{
			delete m_oBricks[i];
			m_oBricks[i] = 0;
		}
	}
}

void Wall::Init()
{
	SetX(WALL_BEGIN_X);
	SetY(WALL_BEGIN_Y);
	SetWidth(WALL_WIDTH);
	SetHeight(WALL_HEIGHT);

	//Init Wall
	int row = 0, col = 0;;
	for (int i = 0; i < TOTAL_BRICKS; ++i)
	{
		if (i < 10)
		{
			m_oBricks[i] = new BrickTexture();
		}
		else
		{
			m_oBricks[i] = new Brick();
			Colors c = static_cast<Colors>(i / BRICKS_FOR_ROW);
			m_oBricks[i]->SetColor(c);
		}

		m_oBricks[i]->NewGame();

		// Set the positions of begin for the bricks
		row = i / BRICKS_FOR_ROW;
		col = i % BRICKS_FOR_ROW;
		m_oBricks[i]->SetPosition(WALL_BEGIN_X + (col * BRICK_WIDTH), WALL_BEGIN_Y - (row * BRICK_HEIGHT));
	}
}

void Wall::NewGame()
{
	// Set all the bricks active
	m_iBricksActive = TOTAL_BRICKS;

	for (int i = 0; i < TOTAL_BRICKS; ++i)
	{
		m_oBricks[i]->SetActive(true);
	}
	
}

void Wall::Render() const
{
	// Render a brick only if it's active
	for (int i = 0; i < TOTAL_BRICKS; ++i)
	{
 		if (m_oBricks[i]->IsActive())
			m_oBricks[i]->Render();
	}
}


void Wall::ChangeBricks()
{
	// Get the active bricks
	Brick bricksActive[TOTAL_BRICKS]; // need to take the maximum possible number of bricks
	bool positionsUsed[TOTAL_BRICKS] = { false };

	for (int i = 0, j = 0; i < TOTAL_BRICKS; ++i)
	{
		if (m_oBricks[i]->IsActive())
		{
			// If the color is Null means that the brick is texture
			bricksActive[j].SetColor(m_oBricks[i]->GetColor());
			// Set every brick not active
			m_oBricks[i]->SetActive(false); 
			// Save the life of the brick
			bricksActive[j++].SetLife(m_oBricks[i]->GetLife());
		}
	}

	int  texture = -1, normal = -1, rand = 0, pos = 0, index = 0, row = 0, col = 0;

	// Random new positions
	for (int i = 0; i < m_iBricksActive; ++i) 
	{
		rand = std::rand() % (TOTAL_BRICKS - i);
		pos = GetFreePosition(positionsUsed,rand);

		if (bricksActive[i].GetColor() == 0)
		{
			index = ++texture;
		}
		else
		{
			index = ++normal + BRICKS_TEXTURE;
			m_oBricks[index]->SetColor(bricksActive[i].GetColor());
		}

		// Set the brick active
		m_oBricks[index]->SetActive(true);

		// Set the life of the brick
		m_oBricks[index]->SetLife(bricksActive[i].GetLife());

		// Update the positions used array
		positionsUsed[pos] = true;

		// Get the beginning position of the brick
		row = pos / BRICKS_FOR_ROW;
		col = pos % BRICKS_FOR_ROW;
		m_oBricks[index]->SetPosition(WALL_BEGIN_X + (col * BRICK_WIDTH), WALL_BEGIN_Y - (row * BRICK_HEIGHT));
		
	}


}

Brick* Wall::GetBrick(int index)
{
	return m_oBricks[index];
}

void Wall::BrickHit()
{
	--m_iBricksActive;
}

int Wall::GetActiveBricks()
{
	return m_iBricksActive;
}

// Get the right position that matches the random value between the free positions in the wall
int Wall::GetFreePosition(bool positions[], int value)
{
	for (int i = 0, j = -1; i < TOTAL_BRICKS; ++i)
	{
		if (!positions[i])
			if (value == ++j)
				return i;
	}
}