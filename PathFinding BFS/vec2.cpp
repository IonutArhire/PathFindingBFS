#include "vec2.h"

vec2::vec2() {}

vec2::vec2(const int x, const int y)
{
	this->x = x;
	this->y = y;
}

void vec2::apply_transition(const vec2& transition)
{
	this->x += transition.x;
	this->y += transition.y;
}

void vec2::reverse_transition(const vec2& transition)
{
	this->x -= transition.x;
	this->y -= transition.y;
}

bool operator==(const vec2& left, const vec2& right)
{
	if (left.x == right.x && left.y == right.y)
	{
		return true;
	}
	return false;
}