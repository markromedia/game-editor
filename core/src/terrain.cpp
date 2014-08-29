#include "terrain.hpp"

#include <iostream>
#include <fstream>
#include <iterator>

#include "opengl.h"
#include <SDL.h>

#include "constants.cpp"
#include "logger.hpp"
#include "game.hpp"
#include "graphics/color4f.hpp"
#include "graphics/quad.hpp"
#include "graphics/texture.hpp"
#include "graphics/texture_manager.hpp"
#include "graphics/frame.hpp"
#include "graphics/render_operation.hpp"
#include "graphics/render_op_manager.hpp"
#include "graphics/vertex_buffer_manager.hpp"
#include "graphics/vertex_buffer.hpp"
#include "graphics/vertex_data.hpp"
#include "data/model_loader.hpp"

Terrain::Terrain()
{
	renderOperation = Graphics::RenderOperationManager::GetDrawModelOp(ModelLoader::SKYBOX);
	renderOperation->Operation_Type = Graphics::RenderOperation::DRAW_TERRAIN;
	renderOperation->Color = Graphics::Color4f(200 / 255.0f, 110 / 255.0f, 0, 1);

	wireframeRenderOperation = Graphics::RenderOperationManager::GetDrawWireframeOp(ModelLoader::SKYBOX);
	wireframeRenderOperation->Operation_Type = Graphics::RenderOperation::DRAW_WIREFRAME;
}

void Terrain::Update( float dt )
{
}

void Terrain::Render()
{
	renderOperation->ModelMatrix = glm::translate(glm::mat4(), glm::vec3(0, 0, 0));
	wireframeRenderOperation->ModelMatrix = glm::translate(glm::mat4(), glm::vec3(0, 0, 0));
	
	//Game::ScreenFrame->QueueRenderOperation(renderOperation, Game::PerspectiveCamera);
	Game::ScreenFrame->QueueRenderOperation(wireframeRenderOperation, Game::PerspectiveCamera);
}


void Terrain::CreateGrid(int grid_width, int grid_height, int grid_size, int height_mult)
{
	std::vector<unsigned char> height_data = ReadHeightMapData("resources/terrain.raw");
	int total_vertices = (grid_width + 1) * (grid_height + 1);
	renderOperation->VertexBuffer = Graphics::VertexBufferManager::GetBuffer(USE_COLOR | USE_NORMAL, total_vertices, (grid_width * grid_height) * 6);
	wireframeRenderOperation->VertexBuffer = Graphics::VertexBufferManager::GetBuffer(0, total_vertices, (grid_width * grid_height) * 6);

	int vertices_row_cnt = grid_height+ 1;
	int vertices_col_cnt = grid_width + 1;
	
	/*
	//convert heightmap into vertices
	for (int y = 0; y < vertices_row_cnt; y++)
	{
		for (int x = 0; x < vertices_col_cnt; x++)
		{
			int index = x + ((grid_height - y) * vertices_col_cnt);
			unsigned int height = height_data[index] * height_mult;

			renderOperation->VertexBuffer->CreateVertex(x * grid_size , height, -y * grid_size);
			wireframeRenderOperation->VertexBuffer->CreateVertex(x * grid_size, height, -y * grid_size);
		}
	}

	//build triangles from vertices
	for (int y = 0; y < grid_height; y++)
	{
		for (int x = 0; x < grid_width; x++)
		{
			int v1i = x + (y * vertices_col_cnt);
			int v2i = x + 1 + (y * vertices_col_cnt);
			int v3i = x + ((y + 1) * vertices_col_cnt);
			int v4i = x + 1 + ((y + 1) * vertices_col_cnt);

			Graphics::Vertex* v1 = renderOperation->VertexBuffer->vertices[v1i];
			Graphics::Vertex* v2 = renderOperation->VertexBuffer->vertices[v2i];
			Graphics::Vertex* v3 = renderOperation->VertexBuffer->vertices[v3i];
			Graphics::Vertex* v4 = renderOperation->VertexBuffer->vertices[v4i];

			renderOperation->VertexBuffer->CreateTriangle(v1, v2, v3);
			renderOperation->VertexBuffer->CreateTriangle(v3, v2, v4);
			
			Graphics::Vertex* wv1 = wireframeRenderOperation->VertexBuffer->vertices[v1i];
			Graphics::Vertex* wv2 = wireframeRenderOperation->VertexBuffer->vertices[v2i];
			Graphics::Vertex* wv3 = wireframeRenderOperation->VertexBuffer->vertices[v3i];
			Graphics::Vertex* wv4 = wireframeRenderOperation->VertexBuffer->vertices[v4i];
			
			wireframeRenderOperation->VertexBuffer->CreateTriangle(wv1, wv2, wv3);
			wireframeRenderOperation->VertexBuffer->CreateTriangle(wv3, wv2, wv4);
		}
	}

	std::vector<glm::vec3> triangle_normals;
	triangle_normals.reserve(6);
	
	//calculate the normals for each vertex
	for (int y = 0; y < vertices_row_cnt; y++)
	{
		for (int x = 0; x < vertices_col_cnt; x++)
		{
			if (has_triangle(x, y, -1, 0, -1, 1, vertices_col_cnt))
				triangle_normals.push_back(triangle_normal(x, y, -1, 0, -1, 1, vertices_col_cnt));
			if (has_triangle(x, y, -1, 1, 0, 1, vertices_col_cnt))
				triangle_normals.push_back(triangle_normal(x, y, -1, 1, 0, 1, vertices_col_cnt));
			if (has_triangle(x, y, 0, 1, 1, 0, vertices_col_cnt))
				triangle_normals.push_back(triangle_normal(x, y, 0, 1, 1, 0, vertices_col_cnt));
			if (has_triangle(x, y, 1, 0, 1, -1, vertices_col_cnt))
				triangle_normals.push_back(triangle_normal(x, y, 1, 0, 1, -1, vertices_col_cnt));
			if (has_triangle(x, y, 1, -1, -1, -1, vertices_col_cnt))
				triangle_normals.push_back(triangle_normal(x, y, 1, -1, -1, -1, vertices_col_cnt));
			if (has_triangle(x, y, -1, -1, -1, 0, vertices_col_cnt))
				triangle_normals.push_back(triangle_normal(x, y, -1, -1, -1, 0, vertices_col_cnt));

			glm::vec3 average;
			for(int i = 0; i < triangle_normals.size(); i++) {
				glm::vec3 c_vec = triangle_normals[i];
				average += triangle_normals[i];
			}

			average = glm::vec3(average.x / triangle_normals.size(), average.y / triangle_normals.size(), average.z / triangle_normals.size());

			Graphics::Vertex* v = renderOperation->VertexBuffer->vertices[x + (y * vertices_col_cnt)];
			v->normal(average);

			//assign color based on normal
			assignColor(v, average);

			triangle_normals.clear();
		}
	}
	*/
	CreateCubeFace(grid_width, grid_height, grid_size, glm::vec3(1, 0, 0), glm::vec3(0, 1, 0), glm::vec3(0, 0, -1));
}

glm::vec3 Terrain::triangle_normal(int x, int y, int offset_x1, int offset_y1, int offset_x2, int offset_y2, const int&  num_cols)
{
	int i1 =  x + offset_x1 + ((y + offset_y1) * num_cols);	
	int i2 =  x + (y * num_cols);	
	int i3 =  x + offset_x2 + ((y + offset_y2) * num_cols);	

	Graphics::Vertex* v1 = renderOperation->VertexBuffer->vertices[i1];
	Graphics::Vertex* v2 = renderOperation->VertexBuffer->vertices[i2];
	Graphics::Vertex* v3 = renderOperation->VertexBuffer->vertices[i3];

	glm::vec3 v1v = glm::vec3(v1->x.value(), v1->y.value(), v1->z.value());
	glm::vec3 v2v = glm::vec3(v2->x.value(), v2->y.value(), v2->z.value());
	glm::vec3 v3v = glm::vec3(v3->x.value(), v3->y.value(), v3->z.value());

	glm::vec3 normal = glm::normalize(glm::cross(v1v - v2v, v2v - v3v));
	return normal;
}

bool Terrain::has_triangle(int x, int y, int offset_x1, int offset_y1, int offset_x2, int offset_y2, const int&  num_cols)
{
	int v1 =  x + offset_x1 + ((y + offset_y1) * num_cols);
	int v2 =  x + offset_x2 + ((y + offset_y2) * num_cols);

	return v1 >= 0 && v1 < renderOperation->VertexBuffer->vertices.size()
		&& v2 >= 0 && v2 < renderOperation->VertexBuffer->vertices.size();
}


std::vector<unsigned char> Terrain::ReadHeightMapData(std::string file)
{
	std::ifstream heightmap_file(file, std::ios::binary);
	std::vector<unsigned char> file_data((std::istreambuf_iterator<char>(heightmap_file)), std::istreambuf_iterator<char>());
	heightmap_file.close();

	return file_data;
}

void Terrain::assignColor(Graphics::Vertex* v, glm::vec3 normalized_normal)
{
	float angle =  glm::angle(normalized_normal, glm::vec3(normalized_normal.x, 0, normalized_normal.z));

	if (angle > 70 && angle < 110)
		v->rgba(100 / 255.0f, 200 / 255.0f, 0, 1); //green
	else
		v->rgba(200 / 255.0f, 110 / 255.0f, 0, 1); //brown
}

void Terrain::CreateCubeFace(int grid_width, int grid_height, float vertex_length_width, glm::vec3 width_dir, glm::vec3 length_dir, glm::vec3 height_dir)
{
	int vertices_row_cnt = grid_height+ 1;
	int vertices_col_cnt = grid_width + 1;

	for (int y = 0; y < vertices_row_cnt; y++)
	{
		for (int x = 0; x < vertices_col_cnt; x++)
		{
			//int index = x + ((grid_height - y) * vertices_col_cnt);
			//unsigned int height = height_data[index] * height_mult;
			glm::vec3 position = (x * vertex_length_width * width_dir) + (y * vertex_length_width * length_dir) + (0.0f * height_dir);

			renderOperation->VertexBuffer->CreateVertex(position.x, position.y, position.z);
			wireframeRenderOperation->VertexBuffer->CreateVertex(position.x, position.y, position.z);
		}
	}

	//build triangles from vertices
	for (int y = 0; y < grid_height; y++)
	{
		for (int x = 0; x < grid_width; x++)
		{
			int v1i = x + (y * vertices_col_cnt);
			int v2i = x + 1 + (y * vertices_col_cnt);
			int v3i = x + ((y + 1) * vertices_col_cnt);
			int v4i = x + 1 + ((y + 1) * vertices_col_cnt);

			Graphics::Vertex* v1 = renderOperation->VertexBuffer->vertices[v1i];
			Graphics::Vertex* v2 = renderOperation->VertexBuffer->vertices[v2i];
			Graphics::Vertex* v3 = renderOperation->VertexBuffer->vertices[v3i];
			Graphics::Vertex* v4 = renderOperation->VertexBuffer->vertices[v4i];

			renderOperation->VertexBuffer->CreateTriangle(v1, v2, v3);
			renderOperation->VertexBuffer->CreateTriangle(v3, v2, v4);

			Graphics::Vertex* wv1 = wireframeRenderOperation->VertexBuffer->vertices[v1i];
			Graphics::Vertex* wv2 = wireframeRenderOperation->VertexBuffer->vertices[v2i];
			Graphics::Vertex* wv3 = wireframeRenderOperation->VertexBuffer->vertices[v3i];
			Graphics::Vertex* wv4 = wireframeRenderOperation->VertexBuffer->vertices[v4i];

			wireframeRenderOperation->VertexBuffer->CreateTriangle(wv1, wv2, wv3);
			wireframeRenderOperation->VertexBuffer->CreateTriangle(wv3, wv2, wv4);
		}
	}
}



