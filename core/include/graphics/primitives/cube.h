//
//  cube.h
//  Flight
//
//  Created by Mark Udit on 9/10/14.
//
//

#ifndef __Flight__cube__
#define __Flight__cube__

#include <iostream>
#include "graphics/gllogger.hpp"
#include "graphics/vertex_buffer.hpp"
using namespace Graphics;


class Cube {
private:
    //basic dimensions
    int _width, _height, _depth;
    
    //the vertex buffer
    VertexBuffer * _buffer;
public:
    Cube(int flags, int width, int height, int depth);
};

#endif /* defined(__Flight__cube__) */
