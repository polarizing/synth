#include "grid.h"

Grid::Grid() {

}

void Grid::setup() {
	colWidth = ofGetWidth() / cols;
	rowWidth = ofGetHeight() / rows;
}
void Grid::toggleCell(ofVec2f mousePos) {
	int colIndex = mousePos.x / colWidth;
	int rowIndex = mousePos.y / rowWidth;

	if (grid[rowIndex][colIndex] == 1)
	{
		grid[rowIndex][colIndex] = 0;
		pattern[colIndex] = -1;
	}
	else
	{
		grid[rowIndex][colIndex] = 1;
		pattern[colIndex] = rowIndex;
	}
	for (const auto& e : pattern) {
		std::cout << e << std::endl;
	}
	std::cout << "" << std::endl;
}
void Grid::draw() {
	ofNoFill();
	ofSetLineWidth(2.0);
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			if (grid[i][j] == 1)
			{
				ofSetColor(ofColor::blue);
				ofFill();
				ofDrawRectangle(j*colWidth, i*rowWidth, colWidth, rowWidth);
			}
			else {
				ofNoFill();
				ofSetColor(ofColor::white);
				ofDrawRectangle(j*colWidth, i*rowWidth, colWidth, rowWidth);
			}
		}
	}
}