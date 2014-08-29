#include "terrain.hpp"

#include <iostream>
#include <fstream>
#include<iterator>

#include "opengl.h"
#include <sdl2/SDL.h>

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
	
	Game::ScreenFrame->QueueRenderOperation(renderOperation, Game::PerspectiveCamera);
	Game::ScreenFrame->QueueRenderOperation(wireframeRenderOperation, Game::PerspectiveCamera);
}


void Terrain::CreateGrid(int rows, int cols, int grid_size)
{
	std::vector<unsigned char> height_data = ReadHeightMapData("resources/terrain.raw");
	int total_vertices = (rows + 1) * (cols + 1);
	renderOperation->VertexBuffer = Graphics::VertexBufferManager::GetBuffer(USE_COLOR | USE_NORMAL, total_vertices, (rows * cols) * 6);
	wireframeRenderOperation->VertexBuffer = Graphics::VertexBufferManager::GetBuffer(0, total_vertices, (rows * cols) * 6);
    
	int vertices_row_cnt = rows + 1;
	int vertices_col_cnt = cols + 1;
	for (int y = 0; y < vertices_row_cnt; y++)
	{
		for (int x = 0; x < vertices_col_cnt; x++)
		{
			int index = x + ((rows - y) * vertices_col_cnt);
			unsigned int height = height_data[index] * 40;
			renderOperation->VertexBuffer->CreateVertex(x * grid_size , y * grid_size, height);
			wireframeRenderOperation->VertexBuffer->CreateVertex(x * grid_size, y * grid_size, height);
		}
	}
    
	for (int y = 0; y < rows; y++)
	{
		for (int x = 0; x < cols; x++)
		{
			int v1i = x + (y * (cols + 1));
			int v2i = x + 1 + (y * (cols + 1));
			int v3i = x + ((y + 1) * (cols + 1));
			int v4i = x + 1 + ((y + 1) * (cols + 1));
            
			Graphics::Vertex* v1 = renderOperation->VertexBuffer->vertices[v1i];
			Graphics::Vertex* v2 = renderOperation->VertexBuffer->vertices[v2i];
			Graphics::Vertex* v3 = renderOperation->VertexBuffer->vertices[v3i];
			Graphics::Vertex* v4 = renderOperation->VertexBuffer->vertices[v4i];
            
			renderOperation->VertexBuffer->CreateTriangle(v1, v2, v3);
			renderOperation->VertexBuffer->CreateTriangle(v3, v2, v4);
            
			//set the normals for each vertex
			glm::vec3 v1v = glm::vec3(v1->x.value(), v1->y.value(), v1->z.value());
			glm::vec3 v2v = glm::vec3(v2->x.value(), v2->y.value(), v2->z.value());
			glm::vec3 v3v = glm::vec3(v3->x.value(), v3->y.value(), v3->z.value());
			glm::vec3 v4v = glm::vec3(v4->x.value(), v4->y.value(), v4->z.value());
			
			glm::vec3 v1n = glm::normalize(glm::cross(v4v - v1v, v1v - v2v));
			glm::vec3 v2n = glm::normalize(glm::cross(v1v - v2v, v2v - v3v));
			glm::vec3 v3n = glm::normalize(glm::cross(v2v - v3v, v3v - v4v));
			glm::vec3 v4n = glm::normalize(glm::cross(v3v - v4v, v4v - v1v));
            
			v1->normal(v1n);
			v2->normal(v2n);
			v3->normal(v3n);
			v4->normal(v4n);
            
			//assign color based on normal angle
			assignColor(v1, v1n);
			assignColor(v2, v2n);
			assignColor(v3, v3n);
			assignColor(v4, v4n);
			
			Graphics::Vertex* wv1 = wireframeRenderOperation->VertexBuffer->vertices[v1i];
			Graphics::Vertex* wv2 = wireframeRenderOperation->VertexBuffer->vertices[v2i];
			Graphics::Vertex* wv3 = wireframeRenderOperation->VertexBuffer->vertices[v3i];
			Graphics::Vertex* wv4 = wireframeRenderOperation->VertexBuffer->vertices[v4i];
			
			wireframeRenderOperation->VertexBuffer->CreateTriangle(wv1, wv2, wv3);
			wireframeRenderOperation->VertexBuffer->CreateTriangle(wv3, wv2, wv4);
		}
	}
}

std::vector<unsigned char> Terrain::ReadHeightMapData(char* filename)
{
	std::ifstream heightmap_file(filename, std::ios::binary);
	std::vector<unsigned char> file_data((std::istreambuf_iterator<char>(heightmap_file)), std::istreambuf_iterator<char>());
	heightmap_file.close();
    
	return file_data;
}

void Terrain::assignColor(Graphics::Vertex* v, glm::vec3 normalized_normal)
{
	float angle =  glm::angle(normalized_normal, glm::vec3(normalized_normal.x, normalized_normal.y, 0));
    
	if (angle > 80 && angle < 100)
		v->rgba(100 / 255.0f, 200 / 255.0f, 0, 1);
	else
		v->rgba(200 / 255.0f, 110 / 255.0f, 0, 1);
}
