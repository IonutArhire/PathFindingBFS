#pragma once

#include "play_grid.h"

#include <SDL.h>


class main_game
{
private:	
	SDL_Window* window_;
	SDL_Renderer* rend_;

	SDL_Event event_;
	
	play_grid grid_;
	
	bool quit;
	bool is_left_down_;
	bool is_right_down_;
	
	void init_grid();

	bool init_systems();
	
	void close();
	
	void game_loop();

	void reset_game();
	
public:
	main_game();

	~main_game();
	
	void run();
};
