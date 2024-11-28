#ifndef SHAPE_H
#define SHAPE_H
#include <vector>
#include "shapeObserver.h"

using namespace std;

class Shape {
	protected:
		vector<vector<char>> grid;
		vector<vector<char>> shape;
		int o_top, i_top, o_left, i_left, o_width, i_width, o_height, i_height;
		char c;

        vector<ShapeObserver*> observers;

	public:
		Shape(int i_width, int i_height, char c);
		void createEmptyShape();
		void createShape(vector<vector<char>> newShape);
		void addShape();
		void move(int x, int y);
		void rotateCW();
		void rotateCCW();
		char charAt(int x, int y);
		vector<vector<char>> getGrid(); // for testing, can remove

        int getT() { return o_top; }
        int getL() { return o_left; }
        int getWidth();
        int getHeight();

        void attach(ShapeObserver* observer);
        void detach(ShapeObserver* observer);
};

class LShape: public Shape {
	public:
		LShape();
};

class IShape: public Shape {
	public:
		IShape();
};

class JShape: public Shape {
	public:
		JShape();
};

class OShape: public Shape {
	public:
		OShape();
};

class SShape: public Shape {
	public:
		SShape();
};

class ZShape: public Shape {
	public:
		ZShape();
};

class TShape: public Shape {
	public:
		TShape();
};

class RandShape: public Shape {
	public:
		RandShape();
};

#endif
