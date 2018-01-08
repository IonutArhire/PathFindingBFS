#pragma once

#include "vec2.h"
#include "cell_state.h"

#include <SDL.h>

struct cell
{
private:
	SDL_Rect area_;

	vec2 position_;

	cell_state state_ = FREE;

public:
	cell();

	cell(const cell& cell);

	cell(const vec2 position, const int width, const int height, const cell_state state);

	SDL_Rect get_rekt() const;

	cell_state get_state() const;

	vec2 get_pos() const;

	void set_state(const cell_state state);

	vec2 get_grid_index(const int cell_height, const int cell_width, const int border) const;
};
