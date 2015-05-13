#include "maze.h"

enum direction_facing {NORTH, SOUTH, EAST, WEST};

IRSensorReading g_ir;

Cell::Cell() {
	this->north = 0;	
	this->south = 0;	
	this->east = 0;	
	this->west = 0;
	this->traversed = 0;
	this->dist = -1;
}

void Cell::print_cell(){
	Serial1.print(" N: ");
	Serial1.print(north);
	Serial1.print(" S: ");
	Serial1.print(south);
	Serial1.print(" W: ");
	Serial1.print(west);
	Serial1.print(" E: ");
	Serial1.print(east);
	Serial1.println();
}



Maze::Maze() {
	this->index_x = 0;
	this->index_y = 15;
        this->mouse_direction = NORTH;
}

// void Maze::update_position(int index_x, int index_y) {
// 	this->index_x = index_x;
// 	this->index_y = index_y;
// }

void Maze::update_forwardonecell_position() { //also updates traversed
	int new_index_x = index_x;
	int new_index_y = index_y;
	maze[index_y][index_x].traversed = true;


	if (mouse_direction == NORTH && this->index_y > 0) { 
		new_index_y = this->index_y - 1; 
	}
	else if(mouse_direction == SOUTH && this->index_y < 15) {
		new_index_y = this->index_y + 1;
	}
	else if(mouse_direction == EAST && this->index_x < 15) {
		new_index_x = this->index_x + 1;
	}
	else if(mouse_direction == WEST && this->index_x > 0) { 
		new_index_x = this->index_x - 1;
	}


    this->index_x = new_index_x;
    this->index_y = new_index_y;
}

void Maze::update_turn90left_direction() {
  int temp_mouse_direction = this->mouse_direction;
  if (temp_mouse_direction == NORTH) this->mouse_direction = WEST;
  else if (temp_mouse_direction == WEST) this->mouse_direction = SOUTH;
  else if (temp_mouse_direction == SOUTH) this->mouse_direction = EAST;
  else if (temp_mouse_direction == EAST) this->mouse_direction = NORTH;
}

void Maze::update_turn90right_direction() {
  int temp_mouse_direction = this->mouse_direction;
  if (temp_mouse_direction == NORTH) this->mouse_direction = EAST;
  else if (temp_mouse_direction == EAST) this->mouse_direction = SOUTH;
  else if (temp_mouse_direction == SOUTH) this->mouse_direction = WEST;
  else if (temp_mouse_direction == WEST) this->mouse_direction = NORTH;
}

void Maze::maze_update_wall_sides() {
  float wall_tolerance = 10;
   if (g_ir.left > g_ir.left_wall_threshold - wall_tolerance) { //left wall
     if (this->mouse_direction == NORTH) { (this->maze[this->index_y][this->index_x]).west = 1; }
     else if (this->mouse_direction == EAST) { (this->maze[this->index_y][this->index_x]).north = 1; }
     else if (this->mouse_direction == SOUTH) { (this->maze[this->index_y][this->index_x]).east = 1; }
     else if (this->mouse_direction == WEST) { (this->maze[this->index_y][this->index_x]).south = 1; }
   }
   else { //no left wall
     if (this->mouse_direction == NORTH) { (this->maze[this->index_y][this->index_x]).west = 0; }
     else if (this->mouse_direction == EAST) { (this->maze[this->index_y][this->index_x]).north = 0; }
     else if (this->mouse_direction == SOUTH) { (this->maze[this->index_y][this->index_x]).east = 0; }
     else if (this->mouse_direction == WEST) { (this->maze[this->index_y][this->index_x]).south = 0; }
   }
   
   if (g_ir.right > g_ir.right_wall_threshold - wall_tolerance) { //right wall
     if (this->mouse_direction == NORTH) { (this->maze[this->index_y][this->index_x]).east = 1; }
     else if (this->mouse_direction == EAST) { (this->maze[this->index_y][this->index_x]).south = 1; }
     else if (this->mouse_direction == SOUTH) { (this->maze[this->index_y][this->index_x]).west = 1; }
     else if (this->mouse_direction == WEST) { (this->maze[this->index_y][this->index_x]).north = 1; }
   }
   else { //no right wall
     if (this->mouse_direction == NORTH) { (this->maze[this->index_y][this->index_x]).east = 0; }
     else if (this->mouse_direction == EAST) { (this->maze[this->index_y][this->index_x]).south = 0; }
     else if (this->mouse_direction == SOUTH) { (this->maze[this->index_y][this->index_x]).west = 0; }
     else if (this->mouse_direction == WEST) { (this->maze[this->index_y][this->index_x]).north = 0; }     
   }
}

void Maze::maze_update_wall_middle() {
   float wall_tolerance = 10;
   if (g_ir.mid > g_ir.right_wall_threshold - wall_tolerance) { //middle wall
     if (this->mouse_direction == NORTH) { (this->maze[this->index_y][this->index_x]).north = 1; }
     else if (this->mouse_direction == EAST) { (this->maze[this->index_y][this->index_x]).east = 1; }
     else if (this->mouse_direction == SOUTH) { (this->maze[this->index_y][this->index_x]).south = 1; }
     else if (this->mouse_direction == WEST) { (this->maze[this->index_y][this->index_x]).west = 1; }
   }
   else {
     if (this->mouse_direction == NORTH) { (this->maze[this->index_y][this->index_x]).north = 0; }
     else if (this->mouse_direction == EAST) { (this->maze[this->index_y][this->index_x]).east = 0; }
     else if (this->mouse_direction == SOUTH) { (this->maze[this->index_y][this->index_x]).south = 0; }
     else if (this->mouse_direction == WEST) { (this->maze[this->index_y][this->index_x]).west = 0; }
   }
}


void Maze::print_maze_position() {
	Serial1.println("==== POSITION ====");
        Serial1.print("Coordinates: ");
        Serial1.print(this->index_x);
        Serial1.print(", ");
        Serial1.print(this->index_y);
        Serial1.println();
        Serial1.print("Direction: ");
        Serial1.print(this->mouse_direction);
        Serial1.println(); 
//	for(int y = 0; y < 16; ++y){ //row
//		for(int x = 0; x < 16; ++x){ //column
//			if (index_x == x && index_y == y) Serial1.print (" 1");
//			else Serial1.print(" 0");
//		}
//		Serial1.println();
//	}
//	Serial1.println();
}

void Maze::print_maze_traversed() {
	Serial1.println("==== TRAVERSED ====");
	for(int y = 0; y < 16; ++y){ //row
		for(int x = 0; x < 16; ++x){ //column
			if (maze[y][x].traversed == true) Serial1.print (" 1");
			else Serial1.print(" 0");
		}
		Serial1.println();
	}
	Serial1.println();
}

void Maze::print_maze(){
	return;
}




