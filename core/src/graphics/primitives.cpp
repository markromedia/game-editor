//
//  primitives.cpp
//  Flight
//
//  Created by Mark Udit on 10/9/14.
//
//

#include "graphics/primitives.hpp"

Graphics::P::Quad Graphics::Primitives::CreateQuad(VertexBuffer* buffer, int width, int height)
{
    Graphics::Vertex *v1 = buffer->CreateVertex(0,0); //bottom left
	Graphics::Vertex *v2 = buffer->CreateVertex((float) width,0); //bottom right
	Graphics::Vertex *v3 = buffer->CreateVertex(0, (float) height); //top left
    Graphics::Vertex *v4 = buffer->CreateVertex((float) width, (float) height); //top right
	buffer->CreateTriangle(v1, v2, v3);
	buffer->CreateTriangle(v3, v2, v4);
    
    return (Graphics::P::Quad){v1, v2, v3, v4};
}

Graphics::P::Cube Graphics::Primitives::CreateCube(VertexBuffer* buffer, int width, int height, int depth)
{
    float hDepth = depth / 2.0f;
    Graphics::Vertex *v1 = buffer->CreateVertex(0,0, hDepth); //front bottom left
	Graphics::Vertex *v2 = buffer->CreateVertex((float) width,0, hDepth); //front bottom right
	Graphics::Vertex *v3 = buffer->CreateVertex(0, (float) height, hDepth); //front top left
    Graphics::Vertex *v4 = buffer->CreateVertex((float) width, (float) height, hDepth); //front top right
    
    Graphics::Vertex *v5 = buffer->CreateVertex(0,0, -hDepth); //back bottom left
	Graphics::Vertex *v6 = buffer->CreateVertex((float) width,0, -hDepth); //back bottom right
	Graphics::Vertex *v7 = buffer->CreateVertex(0, (float) height, -hDepth); //back top left
    Graphics::Vertex *v8 = buffer->CreateVertex((float) width, (float) height, -hDepth); //back top right
    
    //front
    buffer->CreateTriangle(v1, v2, v3);
	buffer->CreateTriangle(v3, v2, v4);
    //back
    buffer->CreateTriangle(v6, v5, v8);
	buffer->CreateTriangle(v8, v5, v7);
    //top
    buffer->CreateTriangle(v3, v4, v7);
	buffer->CreateTriangle(v7, v4, v8);
    //bottom
    buffer->CreateTriangle(v5, v6, v1);
	buffer->CreateTriangle(v1, v6, v2);
    //left
    buffer->CreateTriangle(v5, v1, v7);
	buffer->CreateTriangle(v7, v1, v3);
    //right
    buffer->CreateTriangle(v2, v6, v4);
	buffer->CreateTriangle(v4, v6, v8);


    
    return (Graphics::P::Cube){v1, v2, v3, v4, v5, v6, v7, v8};
}

