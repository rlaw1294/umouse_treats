#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include <Arduino.h>
#include "setup.h"


class Cell {
	public:
		boolean north;
		boolean south;
		boolean west;
		boolean east;
		boolean traversed;
		int dist;

		//functions
		Cell();
		void print_cell();
};

class Maze {
	private:
		Cell maze[16][16];
		int index_x; //x position
		int index_y; //y position
		int mouse_direction;

	public:
		Maze();
		void print_maze();
		void print_maze_position();
		void print_maze_traversed();

		// void update_maze_position();
		void update_forwardonecell_position();
                void update_turn90left_direction();
                void update_turn90right_direction();
                void maze_update_wall_sides();
                void maze_update_wall_middle();
};

#endif

