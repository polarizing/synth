#pragma once
#include "ofMain.h"

class Grid {

public:
	void setup();
	void update();
	void draw();

	void toggleCell(ofVec2f mousePos);
	int* getPattern();

	int grid[8][8] = { {0} };
	int cols = 8;
	int rows = 8;
	int colWidth;
	int rowWidth;
	int pattern[8] = { -1, -1, -1, -1, -1, -1, -1, -1 };
	
	Grid();

private:

};
