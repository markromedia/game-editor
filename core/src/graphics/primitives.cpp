//
//  primitives.cpp
//  Flight
//
//  Created by Mark Udit on 10/9/14.
//
//

#include "graphics/primitives.hpp"

Graphics::Quad::Quad()
{
}

Graphics::Quad Graphics::Primitives::CreateQuad(VertexBuffer* buffer, int width, int height, Graphics::Color4f* vertex_color)
{
	float hWidth = width / 2.0f;
	float hHeight = height / 2.0f;
    Graphics::Vertex *v1 = buffer->CreateVertex(-hWidth,-hHeight); //bottom left
	Graphics::Vertex *v2 = buffer->CreateVertex(hWidth,-hHeight); //bottom right
	Graphics::Vertex *v3 = buffer->CreateVertex(-hWidth, hHeight); //top left
    Graphics::Vertex *v4 = buffer->CreateVertex(hWidth, hHeight); //top right
	buffer->CreateTriangle(v1, v2, v3);
	buffer->CreateTriangle(v3, v2, v4);
    
	if (vertex_color != NULL)
	{
		v1->rgba(vertex_color->r, vertex_color->g, vertex_color->b, vertex_color->a);
		v2->rgba(vertex_color->r, vertex_color->g, vertex_color->b, vertex_color->a);
		v3->rgba(vertex_color->r, vertex_color->g, vertex_color->b, vertex_color->a);
		v4->rgba(vertex_color->r, vertex_color->g, vertex_color->b, vertex_color->a);
	}

    return Graphics::Quad(v1, v2, v3, v4);
}

Graphics::Cube Graphics::Primitives::CreateCube(VertexBuffer* buffer, int width, int height, int depth, Graphics::Color4f* vertex_color)
{
	return CreateCube(buffer, width, height, depth, glm::vec3(0,0,0), vertex_color);
}

Graphics::Cube Graphics::Primitives::CreateCube(VertexBuffer* buffer, int width, int height, int depth, glm::vec3 offset, Graphics::Color4f* vertex_color)
{
	float hDepth = depth / 2.0f;
	float hWidth = width / 2.0f;
	float hHeight = height / 2.0f;
    Graphics::Vertex *v1 = buffer->CreateVertex(-hWidth + offset.x, -hHeight + offset.y, hDepth + offset.z); //front bottom left
	Graphics::Vertex *v2 = buffer->CreateVertex(hWidth + offset.x, -hHeight + offset.y, hDepth + offset.z); //front bottom right
	Graphics::Vertex *v3 = buffer->CreateVertex(-hWidth + offset.x,  hHeight + offset.y, hDepth + offset.z); //front top left 
    Graphics::Vertex *v4 = buffer->CreateVertex(hWidth + offset.x,  hHeight + offset.y, hDepth + offset.z); //front top right
    
    Graphics::Vertex *v5 = buffer->CreateVertex(-hWidth + offset.x, -hHeight + offset.y, -hDepth + offset.z); //back bottom left
	Graphics::Vertex *v6 = buffer->CreateVertex(hWidth + offset.x, -hHeight + offset.y, -hDepth + offset.z); //back bottom right
	Graphics::Vertex *v7 = buffer->CreateVertex(-hWidth + offset.x,  hHeight + offset.y, -hDepth + offset.z); //back top left
    Graphics::Vertex *v8 = buffer->CreateVertex(hWidth + offset.x,  hHeight + offset.y, -hDepth + offset.z); //back top right
    
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

	if (vertex_color != NULL)
	{
		v1->rgba(vertex_color->r, vertex_color->g, vertex_color->b, vertex_color->a);
		v2->rgba(vertex_color->r, vertex_color->g, vertex_color->b, vertex_color->a);
		v3->rgba(vertex_color->r, vertex_color->g, vertex_color->b, vertex_color->a);
		v4->rgba(vertex_color->r, vertex_color->g, vertex_color->b, vertex_color->a);
		v5->rgba(vertex_color->r, vertex_color->g, vertex_color->b, vertex_color->a);
		v6->rgba(vertex_color->r, vertex_color->g, vertex_color->b, vertex_color->a);
		v7->rgba(vertex_color->r, vertex_color->g, vertex_color->b, vertex_color->a);
		v8->rgba(vertex_color->r, vertex_color->g, vertex_color->b, vertex_color->a);
	}

    return Graphics::Cube(v1, v2, v3, v4, v5, v6, v7, v8);
}

Graphics::Grid Graphics::Primitives::CreateGrid(VertexBuffer* buffer, 
												int num_rows, int num_cols, 
												float row_spacing, float col_spacing, 
												float line_thickness, 
												Graphics::Color4f* vertex_color)
{
	float x_lines_start = ((num_rows + 1) / 2) * row_spacing;
	float x_lines_length = num_cols * col_spacing;
	float z_lines_start = ((num_cols + 1) / 2) * col_spacing;
	float z_lines_length = num_rows * row_spacing;

	for (int i = 0; i < num_rows + 1; i++)
	{
		CreateCube(buffer, x_lines_length, line_thickness, line_thickness, glm::vec3(0, 0, x_lines_start + (i * -row_spacing)), vertex_color);
	}

	for (int i = 0; i < num_cols + 1; i++)
	{
		CreateCube(buffer, line_thickness, line_thickness, z_lines_length, glm::vec3(z_lines_start + (i * -col_spacing), 0, 0), vertex_color);
	}
	return Graphics::Grid(std::vector<Graphics::Cube>());
}

