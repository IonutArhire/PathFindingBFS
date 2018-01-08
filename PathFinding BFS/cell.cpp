#include "cell.h"

cell::cell() {}

cell::cell(const cell& cell)
{
	vec2 position = cell.get_pos();
	int width = cell.get_rekt().w;
	int height = cell.get_rekt().h;
	cell_state state = cell.get_state();

	position_.x = position.x;
	position_.y = position.y;

	area_.x = position.x;
	area_.y = position.y;
	area_.w = width;
	area_.h = height;

	state_ = state;
}

cell::cell(const vec2 position, const int width, const int height, const cell_state state)
{
	position_.x = position.x;
	position_.y = position.y;

	area_.x = position.x;
	area_.y = position.y;
	area_.w = width;
	area_.h = height;

	state_ = state;
}

SDL_Rect cell::get_rekt() const
{
	return area_;
}

cell_state cell::get_state() const
{
	return state_;
}

vec2 cell::get_pos() const
{
	return position_;
}

void cell::set_state(const cell_state state)
{
	state_ = state;
}

vec2 cell::get_grid_index(const int cell_height, const int cell_width, const int border) const
{
	int x = position_.x - border;
	int y = position_.y - border;

	int cellX = int(y / cell_height);
	int cellY = int(x / cell_width);

	vec2 index(cellX, cellY);

	return index;
}
