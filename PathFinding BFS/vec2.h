#pragma once

struct vec2
{
	int x;
	int y;

	vec2();

	vec2(const int x, const int y);

	void apply_transition(const vec2& transition);

	void reverse_transition(const vec2& transition);

	bool friend operator ==(const vec2& left, const vec2& right);
};
