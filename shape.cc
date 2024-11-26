#include "shape.h"
#include <iostream>
using namespace std;

Shape::Shape(int i_width, int i_height, char c): 
			o_top{0}, i_top{0}, o_left{0}, i_left{0}, o_width{4}, i_width{i_width}, o_height{4}, i_height{i_height}, c{c} 
{ // tested
	createEmptyShape();
}

void Shape::createEmptyShape() { // tested
	if (grid.size() > 0) grid.clear();

	vector<char> r1, r2, r3, r4;
	r1.insert(r1.end(), {' ', ' ', ' ', ' '});
	r2.insert(r2.end(), {' ', ' ', ' ', ' '});
	r3.insert(r3.end(), {' ', ' ', ' ', ' '});
	r4.insert(r4.end(), {' ', ' ', ' ', ' '});
	grid.insert(grid.end(), {r1, r2, r3, r4});
}

void Shape::move(int x, int y) {
	o_left += x;
	o_top += y;
};

void Shape::createShape(vector<vector<char>> newShape) { // tested
	shape.clear();
	i_width = newShape[0].size();
	i_height = newShape.size();

	for (int i = 0; i < i_height; ++i) {
		vector<char> row;
		for (int j = 0; j < i_width; ++j) {
			row.emplace_back(newShape[i][j]);
		}
		shape.emplace_back(row);
	}
}

void Shape::addShape() { // tested
	for (int i = i_top; i < i_top + i_height; ++i) {
		for (int j = i_left; j < i_left + i_width; ++j) {
			grid[i][j] = shape[i-i_top][j-i_left];
		}
	}
}

char Shape::charAt(int x, int y) { return grid[y][x]; } // tested

void Shape::rotateCW() { //tested 
	int n = grid.size();
	vector<vector<char>> temp{grid};

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			temp[j][n-i-1] = grid[i][j];
		}
	}

	int newTop = i_left;
	i_left = n - (i_top + i_height);
	i_top = newTop;

	std::swap(i_height, i_width);

	vector<vector<char>> newShape;

	for (int i = i_top; i < i_top + i_height; ++i) {
		vector<char> row;
		for (int j = i_left; j < i_left + i_width; ++j) {
			row.emplace_back(temp[i][j]);
		}

		newShape.emplace_back(row);
	}

	i_top = 0;
	i_left = 0;

	createShape(newShape);
	createEmptyShape();
	addShape();
}

void Shape::rotateCCW() { // tested
	int n = grid.size();
	vector<vector<char>> temp{grid};

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			temp[n-j-1][i] = grid[i][j];
		}
	}	

	int newLeft = i_top;
    i_top = n - (i_left + i_width);
    i_left = newLeft;

	std::swap(i_height, i_width);

	vector<vector<char>> newShape;

	for (int i = i_top; i < i_top + i_height; ++i) {
		vector<char> row;
		for (int j = i_left; j < i_left + i_width; ++j) {
			row.emplace_back(temp[i][j]);
		}

		newShape.emplace_back(row);
	}

	i_top = 0;
	i_left = 0;

	createShape(newShape);
	createEmptyShape();
	addShape();
}

vector<vector<char>> Shape::getGrid() { return grid;} //tested

LShape::LShape(): Shape{3, 2, 'L'}  { //tested
	vector<char> r1, r2;
	r1.insert(r1.end(), {' ', ' ', c});
	r2.insert(r2.end(), {c, c, c});
	shape.insert(shape.end(), {r1, r2});

	addShape();
}

IShape::IShape(): Shape{4, 1, 'I'}  { //tested
	vector<char> r1;
	r1.insert(r1.end(), {c, c, c, c});
	shape.insert(shape.end(), {r1});

	addShape();
}

JShape::JShape(): Shape{3, 2, 'J'}  { //tested
	vector<char> r1, r2;
	r1.insert(r1.end(), {c, ' ', ' '});
	r2.insert(r2.end(), {c, c, c});
	shape.insert(shape.end(), {r1, r2});

	addShape();
}

OShape::OShape(): Shape{2, 2, 'O'}  { //tested
	vector<char> r1, r2;
	r1.insert(r1.end(), {c, c});
	r2.insert(r2.end(), {c, c});
	shape.insert(shape.end(), {r1, r2});

	addShape();
}

SShape::SShape(): Shape{3, 2, 'S'}  { //tested
	vector<char> r1, r2;
	r1.insert(r1.end(), {' ', c, c});
	r2.insert(r2.end(), {c, c, ' '});
	shape.insert(shape.end(), {r1, r2});

	addShape();
}

ZShape::ZShape(): Shape{3, 2, 'Z'}  { //tested
	vector<char> r1, r2;
	r1.insert(r1.end(), {c, c, ' '});
	r2.insert(r2.end(), {' ', c, c});
	shape.insert(shape.end(), {r1, r2});

	addShape();
}

TShape::TShape(): Shape{3, 2, 'T'}  { //tested
	vector<char> r1, r2;
	r1.insert(r1.end(), {c, c, c});
	r2.insert(r2.end(), {' ', c, ' '});
	shape.insert(shape.end(), {r1, r2});

	addShape();
}
