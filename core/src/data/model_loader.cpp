#include "data/model_loader.hpp"

#include "graphics/vertex_buffer.hpp"
#include "graphics/vertex_buffer_manager.hpp"

extern "C"
{
	#include "data/model/enemy.h"
	#include "data/model/torus.h"
	#include "data/model/cube.h"
	#include "data/model/teapot.h"
	#include "data/model/falcon.h"
	#include "data/model/station.h"
	#include "data/model/cube2.h"
	#include "data/model/skybox.h"
};

#define NUM_ELEMENTS 8

graphics::VertexBuffer* ModelLoader::LoadModel(int model)
{
	double* vertices;
	short* indices;
	int num_vertices, num_indices;

	switch (model) {
	case ModelLoader::CUBE1 :
		{
			vertices = &cube_vertices[0];
			indices = &cube_indices[0];
			num_vertices = cube_num_vertices;
			num_indices = cube_num_indices;
			break;
		}
	case ModelLoader::ENEMY : 
		{
			vertices = &enemy_vertices[0];
			indices = &enemy_indices[0];
			num_vertices = enemy_num_vertices;
			num_indices = enemy_num_indices;
			break;
		}
	case ModelLoader::TEAPOT : 
		{
			vertices = &teapot_vertices[0];
			indices = &teapot_indices[0];
			num_vertices = teapot_num_vertices;
			num_indices = teapot_num_indices;
			break;
		}
	case ModelLoader::TORUS : 
		{
			vertices = &torus_vertices[0];
			indices = &torus_indices[0];
			num_vertices = torus_num_vertices;
			num_indices = torus_num_indices;
			break;
		}
	case ModelLoader::FALCON : 
		{
			vertices = &falcon_vertices[0];
			indices = &falcon_indices[0];
			num_vertices = falcon_num_vertices;
			num_indices = falcon_num_indices;
			break;
		}
	case ModelLoader::STATION : 
		{
			vertices = &station_vertices[0];
			indices = &station_indices[0];
			num_vertices = station_num_vertices;
			num_indices = station_num_indices;
			break;
		}
	case ModelLoader::CUBE2 : 
		{
			vertices = &cube2_vertices[0];
			indices = &cube2_indices[0];
			num_vertices = cube2_num_vertices;
			num_indices = cube2_num_indices;
			break;
		}
	case ModelLoader::SKYBOX : 
		{
			vertices = &skybox_vertices[0];
			indices = &skybox_indices[0];
			num_vertices = skybox_num_vertices;
			num_indices = skybox_num_indices;
			break;
		}
	default : 
		{
			vertices = &skybox_vertices[0];
			indices = &skybox_indices[0];
			num_vertices = skybox_num_vertices;
			num_indices = skybox_num_indices;
			break;
		}
	}

	graphics::VertexBuffer* buf = graphics::VertexBufferManager::GetBuffer(USE_TEXTURE | USE_NORMAL, num_vertices, num_indices);
	
	for (int i = 0; i < num_vertices; i++)
	{
		int idx = NUM_ELEMENTS * i;

		//x, y, z
		buf->iva_data.push_back((float) vertices[idx]);
		buf->iva_data.push_back((float) vertices[idx + 1]);
		buf->iva_data.push_back((float) vertices[idx + 2]);
		//u, v
		buf->iva_data.push_back((float) vertices[idx + 3]);
		buf->iva_data.push_back((float) vertices[idx + 4]);
		//normal x, y, z
		buf->iva_data.push_back((float) vertices[idx + 5]);
		buf->iva_data.push_back((float) vertices[idx + 6]);
		buf->iva_data.push_back((float) vertices[idx + 7]);
	}

	for (int i = 0; i < num_indices; i++)
	{
		buf->indices_buffer.push_back(indices[i]);
	}

	buf->data_is_dirty = true;

	return buf;
}