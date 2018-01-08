#pragma once

#include "node.h"

#include <string>

node::node() {}

node::node(vec2 position, node* parent)
{
	this->position = position;
	this->parent = parent;
}

bool operator==(const node& left, const node& right)
{
	return left.position == right.position;
}

size_t node_hasher::operator()(const node& node) const
{
	std::string aggregator = std::to_string(node.position.x) + std::to_string(node.position.y);
	return std::hash<std::string>()(aggregator);
}
