#ifndef SHAPEOBSERVER
#define SHAPEOBSERVER

#include "shape.h"

class ShapeObserver {
public:
    virtual ~ShapeObserver() = default;
    virtual void onShapeMoved(Shape* shape, int oldX, int oldY) = 0;
};

#endif