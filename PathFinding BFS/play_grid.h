#pragma once

#include "cell.h"

#include <SDL.h>
#include <vector>

struct node;

class play_grid
{
private:
	int screen_width_;
	int screen_height_;
	int num_of_cells_per_row_;
	int border_;
	
	int cell_width_;
	int cell_height_;

	SDL_Renderer* rend_;
	
	cell cells_[150][150];

	cell* start = nullptr;

	cell* goal = nullptr;

	void BFS(vec2 initial, vec2 goal);

	std::vector<vec2> get_ordered_transitions();

	bool is_node_valid(node& node);

public:
	play_grid();

	~play_grid();

	void init(int screen_width, int screen_height, int num_of_cells_per_row, int border, SDL_Renderer* rend);

	void update(const bool is_left_down, const bool is_right_down, int x, int y);
	
	void draw();

	void reset_grid();
};
