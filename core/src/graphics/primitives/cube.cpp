//
//  cube.cpp
//  Flight
//
//  Created by Mark Udit on 9/10/14.
//
//

#include "cube.h"

#include "../vertex_buffer_manager.hpp"

Cube::Cube(int flags, int width, int height, int depth) : _width(width), _height(height), _depth(depth)
{
    this->_buffer = Graphics::VertexBufferManager::GetBuffer(flags);
}