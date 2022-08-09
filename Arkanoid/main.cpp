#pragma once

#include <iostream>
#include <SDL.h>

#include "game.h"

#define SDL_TIMEREVENT SDL_USEREVENT
const int FPS = 60;
bool quitGame = false;
bool isLeftPressed = false;
bool isRightPressed = false;

SDL_Window *win;
SDL_GLContext glcontext;
Game* game;


unsigned int pushTimerEvent(unsigned int, void*)
{
	SDL_Event e;
	e.type = SDL_TIMEREVENT;
	SDL_PushEvent(&e);
	return 1000 / FPS;
}

void callbackKeyboard(SDL_Event &e, bool isDown)
{
	int key = e.key.keysym.sym;
	switch (key) {

	case SDLK_ESCAPE:
		quitGame = true;
		break;

	case SDLK_LEFT:
		if (!isDown && isLeftPressed)
		{
			isLeftPressed = false;
			if (!isRightPressed)
				game->ChangeRodDirection(0);
		}
		else if (isDown && game->CanRodMove(false))
		{
			game->ChangeRodDirection(-1.0f);
			isRightPressed = false;
			isLeftPressed = true;
		}
		
		break;

	case SDLK_RIGHT:
		if (!isDown && isRightPressed)
		{
			isRightPressed=false;
			if(!isLeftPressed)
				game->ChangeRodDirection(0);
		}
		else if (isDown && game->CanRodMove(true))
		{
			game->ChangeRodDirection(1.0f);
			isLeftPressed = false;
			isRightPressed = true;
		}
		break;

	case SDLK_SPACE:
		if (!isDown && !game->IsBallMoving())
			game->NewGame();
		break;

	case SDLK_r:
		if (!isDown) 
		{
			game->NewGame();
		}
		break;
	}
}

void callbackTimer(SDL_Event &e)
{
	SDL_GL_MakeCurrent(win, glcontext);

	glOrtho(-1, 1, -1, 1, 0, 0);
	
	if (game->IsAlive())
	{
		game->Update();
		game->Render();
	}
	else
		game->RenderImages();

	SDL_GL_SwapWindow(win);
}

void Cleanup() 
{
	if (game)
	{
		delete game;
		game = 0;
	}

	SDL_GL_DeleteContext(glcontext);

	SDL_DestroyWindow(win);
	win = 0;

	SDL_Quit();
}

void Init() 
{
	glcontext = SDL_GL_CreateContext(win);

	SDL_AddTimer(1000 / FPS, pushTimerEvent, nullptr);

	game = new Game();
	
	game->Init();
}

void processEvent(SDL_Event &e)
{
	switch (e.type)
	{
	case SDL_QUIT: quitGame = true; break;

	case SDL_KEYDOWN: callbackKeyboard(e, true); break;
	case SDL_KEYUP: callbackKeyboard(e, false); break;

	case SDL_TIMEREVENT: callbackTimer(e); break;
	}
}

int main(int, char**)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
		std::cout << "SDL_Init Error: " << SDL_GetError() << std::endl;
		return 1;
	}

	win = SDL_CreateWindow("Arkanoid", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 480, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL);
	if (win == nullptr) {
		std::cout << "SDL_CreateWindow Error: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return 1;
	}

	SDL_ShowCursor(0);

	Init();
	
	while (!quitGame)
	{
		SDL_Event event;
		SDL_WaitEvent(&event);
		processEvent(event);
	}

	Cleanup();

	return 0;
}

