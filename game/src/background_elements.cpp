#include "background_elements.hpp"

#include "opengl.h"
#include <vector>
#include <set>
#include <sstream>
#include <time.h>

#include "graphics/vertex_buffer.hpp"
#include "constants.cpp"

///---------------------------------------------------------------------------------------
Star::Star(Graphics::Vertex* vertex) : vertex(vertex)
{
	Init();
}	

void Star::Init(bool max_y)
{
	vertex->a = time_alive = 0;
	vertex->x = std::rand() % Constants::SCREEN_WIDTH;
	if (max_y)
		vertex->y = Constants::SCREEN_HEIGHT;
	else
		vertex->y = std::rand() % Constants::SCREEN_HEIGHT;

	time_to_live = 5000.0f + std::rand() % 5000;
	mode = 0;
}

void Star::Update(float dt)
{
	time_alive += dt;
	float pct = time_alive / time_to_live;

	if (pct >= 1)
	{
		Init();
		return;
	}  

	switch (mode) {
	case 0:  // appearing
		{
			vertex->a += .01f;
			if (vertex->a >= 1.0f) mode = 1;
			break;
		}
	case 1: // steady
		{
			if (pct >= .5f) mode = 2;
			break;
		}
	case 2: //fading
		{
			vertex->a -= .01f;
			if (vertex->a <= 0) Init();
		}
	}

	//position update
	vertex->y -= velocity;
	if (vertex->y < 0) 
		Init(true);
}
///---------------------------------------------------------------------------------------
Station::Station()
{
	x_position = y_position = z_position = 0;
	rotation_x = rotation_y = rotation_z = 0;
	VertexBuffer = NULL;
	RenderModelOp = NULL;
	RenderWireframeOp = NULL;
}