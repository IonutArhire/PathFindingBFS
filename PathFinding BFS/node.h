#pragma once

#include "vec2.h"

struct node
{
	vec2 position;
	node* parent;

	node();

	node(vec2 position, node* parent);

	bool friend operator ==(const node& left, const node& right);
};

struct node_hasher
{
	size_t operator()(const node& node) const;
};

