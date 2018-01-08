#pragma once

#include "main_game.h"

#include <stdio.h>

#define SCREEN_WIDTH 900
#define SCREEN_HEIGHT 900

#define NUM_OF_CELLS_PER_ROW 80
#define BORDER 10

main_game::main_game()
{
	window_ = nullptr;
	rend_ = nullptr; 
	
	quit = false;
	is_left_down_ = false;
	is_right_down_ = false;
}

main_game::~main_game() {}

bool main_game::init_systems()
{
	bool success = true;
	if( SDL_Init(SDL_INIT_VIDEO) < 0 )
	{
		printf("Unable to initialize SDL! SDL ERROR: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		window_ = SDL_CreateWindow("PathFinding", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if(window_ == NULL)
		{
			printf("Unable to create window! SDL ERROR: %s", SDL_GetError());
			success = false;
		}
		else
		{
			rend_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
			if(rend_ == NULL)
			{
				printf( "Unable to create renderer! SDL ERROR: %s", SDL_GetError());
				success = false;
			}
		}
	}
	return success;
}

void main_game::init_grid()
{
	grid_.init(SCREEN_WIDTH, SCREEN_HEIGHT, NUM_OF_CELLS_PER_ROW, BORDER, rend_);
}

void main_game::close()
{
	SDL_DestroyRenderer(rend_);
	SDL_DestroyWindow(window_);
	
	SDL_Quit();
}

void main_game::run()
{
	if(init_systems())
	{
		init_grid();
		game_loop();
	}
	
	close();
}

void main_game::game_loop()
{
	while(!quit)
	{
		while(SDL_PollEvent(&event_))
		{
			switch(event_.type)
			{
				case SDL_QUIT:
					quit = true;
					break;
				
				case SDL_MOUSEBUTTONDOWN:
					switch(event_.button.button)
					{
						case SDL_BUTTON_LEFT:
						is_left_down_ = true;
						break;
					
						case SDL_BUTTON_RIGHT:
						is_right_down_ = true;
						break;
					
						default: ;
					}
					break;
				
				case SDL_MOUSEBUTTONUP:
					switch(event_.button.button)
					{
						case SDL_BUTTON_LEFT:
						is_left_down_ = false;
						break;
					
						case SDL_BUTTON_RIGHT:
						is_right_down_ = false;
						break;
				
						default: ;
					}
					break;

				case SDL_KEYDOWN:
					switch(event_.key.keysym.sym)
					{
						case SDLK_r:
							reset_game();
							break;

						case SDLK_q:
							quit = true;
					}
			
				default: ;
			}
		}
		grid_.update(is_left_down_, is_right_down_, event_.button.x, event_.button.y);

		SDL_SetRenderDrawColor(rend_, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(rend_);
		
		grid_.draw();
		
		SDL_RenderPresent(rend_);
	}
}

void main_game::reset_game()
{
	grid_.reset_grid();
}










