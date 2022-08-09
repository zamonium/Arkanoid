#pragma once

#include<GL/glew.h>

#define DT 1.0f/60
#define LOWER_BOUND -1
#define UPPER_BOUND 1
#define LEFT_BOUND -1
#define RIGHT_BOUND 1

class GameObject
{
public:
	GameObject() {}
	virtual ~GameObject() {};

	virtual void NewGame() = 0;
	virtual void Update() = 0;
	virtual void Render() const = 0;
};

