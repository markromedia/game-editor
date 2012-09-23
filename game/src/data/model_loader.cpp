#include "model_loader.hpp"

#include "../graphics/vertex_buffer.hpp"
#include "../graphics/vertex_buffer_manager.hpp"
#include "../constants.cpp"

extern "C"
{
	#include "model/enemy.h"
	#include "model/torus.h"
	#include "model/cube.h"
	#include "model/teapot.h"
	#include "model/falcon.h"
	#include "model/station.h"
	#include "model/cube2.h"
};

#define NUM_ELEMENTS 8

Graphics::VertexBuffer* ModelLoader::LoadModel(int model)
{
	double* vertices;
	short* indices;
	int num_vertices, num_indices;

	switch (model) {
	case 0: {
				vertices = &cube_vertices[0];
				indices = &cube_indices[0];
				num_vertices = cube_num_vertices;
				num_indices = cube_num_indices;
				break;
			}
	case 1: {
				vertices = &enemy_vertices[0];
				indices = &enemy_indices[0];
				num_vertices = enemy_num_vertices;
				num_indices = enemy_num_indices;
				break;
			}
	case 2: {
				vertices = &teapot_vertices[0];
				indices = &teapot_indices[0];
				num_vertices = teapot_num_vertices;
				num_indices = teapot_num_indices;
				break;
			}
	case 3: {
				vertices = &torus_vertices[0];
				indices = &torus_indices[0];
				num_vertices = torus_num_vertices;
				num_indices = torus_num_indices;
				break;
			}
	case 4: {
				vertices = &falcon_vertices[0];
				indices = &falcon_indices[0];
				num_vertices = falcon_num_vertices;
				num_indices = falcon_num_indices;
				break;
			}
	case 5: {
				vertices = &station_vertices[0];
				indices = &station_indices[0];
				num_vertices = station_num_vertices;
				num_indices = station_num_indices;
				break;
			}
	case 6: {
				vertices = &cube2_vertices[0];
				indices = &cube2_indices[0];
				num_vertices = cube2_num_vertices;
				num_indices = cube2_num_indices;
				break;
			}
	}

	Graphics::VertexBuffer* buf = Graphics::VertexBufferManager::GetBuffer(USE_TEXTURE | USE_NORMAL, num_vertices, num_indices);
	
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