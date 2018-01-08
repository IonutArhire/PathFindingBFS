#pragma once

#include "play_grid.h"
#include "cell.h"
#include "cell_state.h"
#include "node.h"

#include <queue>
#include <list>
#include <unordered_set>

play_grid::play_grid()
{
	
}

play_grid::~play_grid()
{
	
}
	
void play_grid::init(const int screen_width, const int screen_height, const int num_of_cells_per_row, const int border, SDL_Renderer* rend )
{
	screen_width_ = screen_width;
	screen_height_ = screen_height;
	num_of_cells_per_row_ = num_of_cells_per_row;
	border_ = border;
	
	rend_ = rend;
	
	cell_width_ = int((screen_width - 2 * border) / num_of_cells_per_row_);
	cell_height_ = int((screen_height - 2 * border) / num_of_cells_per_row_);
	
	for( int i = 0; i < num_of_cells_per_row_; i++)
	{
		for( int j = 0; j < num_of_cells_per_row_; j++)
		{
			vec2 vec(border + j * cell_width_, border + i * cell_height_);
			cells_[i][j] = cell(vec, cell_width_, cell_height_, FREE);
		}
	}
}

void play_grid::update(const bool is_left_down, const bool is_right_down, int mouseX, int mouseY)
{
	if (is_left_down && is_right_down)
	{
		return;
	}

	mouseX -= border_;
	mouseY -= border_;

	if (mouseX < 0 || mouseX > screen_width_ - 2 * border_)
	{
		return;
	}

	if (mouseY < 0 || mouseY > screen_height_ - 2 * border_)
	{
		return;
	}

	const int cellX = int(mouseY / cell_height_);
	const int cellY = int(mouseX / cell_width_);

	if (is_left_down)
	{
		if (start == nullptr || goal == nullptr)
		{
			cells_[cellX][cellY].set_state(GOAL);

			if (start == nullptr)
			{
				start = &cells_[cellX][cellY];
			} 
			else if (start != &cells_[cellX][cellY] && goal == nullptr)
			{
				goal = &cells_[cellX][cellY];

				BFS(start->get_grid_index(cell_height_, cell_width_, border_),
				    goal->get_grid_index(cell_height_, cell_width_, border_));
			}
		}
	}

	if (is_right_down)
	{
		cells_[cellX][cellY].set_state(BLOCK);
	}
}

void play_grid::BFS(vec2 initial_position, vec2 goal)
{
	std::list<node> nodes;
	std::queue<node*> open;
	std::unordered_set<node, node_hasher> closed;
	std::vector<vec2> transitions = get_ordered_transitions();

	node* parent_of_root = nullptr;
	nodes.emplace_back(initial_position, parent_of_root);

	open.push(&nodes.front());

	while (!open.empty())
	{
		node& current_node = *open.front();

		closed.insert(current_node);

		for (auto it = transitions.begin(); it != transitions.end(); ++it)
		{
			const vec2 transition = *it;

			current_node.position.apply_transition(transition);

			if (closed.find(current_node) == closed.end())
			{
				if (current_node.position == goal)
				{
					current_node.position.reverse_transition(transition);
					node backtrack_node(current_node.position, current_node.parent);
					while (backtrack_node.parent != nullptr)
					{
						cells_[backtrack_node.position.x][backtrack_node.position.y].set_state(GOAL);
						backtrack_node = *backtrack_node.parent;
					}
					return;
				}

				if (this->is_node_valid(current_node))
				{
					nodes.emplace_back(current_node.position, &current_node);
					open.push(&nodes.back());
					closed.insert(current_node);
				}
			}

			current_node.position.reverse_transition(transition);
		}
		open.pop();
	}
}

void play_grid::draw()
{
	for( int i = 0; i < num_of_cells_per_row_; i++)
	{
		for( int j = 0; j < num_of_cells_per_row_; j++)
		{
			SDL_Rect outlineCell = cells_[i][j].get_rekt();
			switch(cells_[i][j].get_state())
			{
				case FREE:
				break;
				
				case BLOCK:
				SDL_SetRenderDrawColor(rend_, 0, 0, 0, 0xFF);
				SDL_RenderFillRect(rend_, &outlineCell);
				break;
				
				case GOAL:
				SDL_SetRenderDrawColor(rend_, 0, 0xFF, 0, 0xFF);
				SDL_RenderFillRect(rend_, &outlineCell);
				break;
			}
			SDL_SetRenderDrawColor(rend_, 0, 0, 0, 0xFF);
			SDL_RenderDrawRect(rend_, &outlineCell);
		}
	}
}

void play_grid::reset_grid()
{
	for (int i = 0; i < num_of_cells_per_row_; i++)
	{
		for (int j = 0; j < num_of_cells_per_row_; j++)
		{
			cells_[i][j].set_state(FREE);
		}
	}

	start = nullptr;
	goal = nullptr;
}

std::vector<vec2> play_grid::get_ordered_transitions()
{
	std::vector<vec2> ordered_transitions;
	ordered_transitions.push_back(vec2(0, -1));  /*UP*/
	ordered_transitions.push_back(vec2(1, 0));   /*RIGHT*/
	ordered_transitions.push_back(vec2(0, 1));   /*DOWN*/
	ordered_transitions.push_back(vec2(-1, 0));  /*LEFT*/

	ordered_transitions.push_back(vec2(-1, -1)); /*UPPER LEFT*/
	ordered_transitions.push_back(vec2(1, -1));  /*UPPER RIGHT*/
	ordered_transitions.push_back(vec2(1, 1));   /*LOWER RIGHT*/
	ordered_transitions.push_back(vec2(-1, 1));  /*LOWER LEFT*/

	return ordered_transitions;
}

bool play_grid::is_node_valid(node& node)
{
	if (node.position.x >= 0 && node.position.x < num_of_cells_per_row_ && node.position.y >= 0 && node.position.y < num_of_cells_per_row_ &&
		cells_[node.position.x][node.position.y].get_state() != BLOCK)
	{
		return true;
	}
	return false;
}


