#pragma once

#include <cstdlib>

#include "rectangle.h"
#include "brick.h"
#include "bricktexture.h"

#define WALL_WIDTH 0.2f
#define WALL_HEIGHT 0.1f
#define WALL_BEGIN_X -1.0f
#define WALL_BEGIN_Y 0.7f

#define TOTAL_BRICKS 50
#define BRICKS 40
#define BRICKS_TEXTURE 10
#define BRICKS_FOR_ROW 10

class Wall : public Rectangle
{
public:
	Wall() : Rectangle(), m_iBricksActive(0) {};
	~Wall();

	void Init();
	void NewGame();
	void Update() {};
	void Render() const;

	void ChangeBricks();
	Brick* GetBrick(int);
	void BrickHit();
	int GetActiveBricks();

private:
	int GetFreePosition(bool[], int);

	Brick* m_oBricks[TOTAL_BRICKS];
	int m_iBricksActive;
};