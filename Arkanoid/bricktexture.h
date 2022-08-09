#pragma once

#include "brick.h"

class BrickTexture : public Brick
{
public:
	BrickTexture() : Brick() {};
	~BrickTexture() {};

	void Update() {};
	void Render() const;
	bool IsTexture();
};

