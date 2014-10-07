#include "../opengl.h"
#include "quad.hpp"

using namespace Graphics;

Quad::Quad(VertexBuffer* buffer, int width, int height)
{
	v1 = buffer->CreateVertex(0,0); //bottom left
	v2 = buffer->CreateVertex((float) width,0); //bottom right
	v3 = buffer->CreateVertex(0, (float) height); //top left
	v4 = buffer->CreateVertex((float) width, (float) height); //top right
	buffer->CreateTriangle(v1, v2, v3);
	buffer->CreateTriangle(v3, v2, v4);
}