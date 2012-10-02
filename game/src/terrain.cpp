#include "terrain.hpp"

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
	renderOperation = Graphics::RenderOperationManager::GetDrawWireframeOp(ModelLoader::SKYBOX);
	renderOperation->Operation_Type = Graphics::RenderOperation::DRAW_WIREFRAME;
}

void Terrain::Update( float dt )
{
}

void Terrain::Render()
{
	renderOperation->ModelMatrix = glm::translate(glm::mat4(), glm::vec3(0, 0, 0));
	Game::ScreenFrame->QueueRenderOperation(renderOperation, Game::PerspectiveCamera);
}


void Terrain::CreateGrid(int rows, int cols, int grid_size)
{
	int total_vertices = (rows + 1) * (cols + 1);
	renderOperation->VertexBuffer = Graphics::VertexBufferManager::GetBuffer(USE_TEXTURE, total_vertices, (rows * cols) * 6);
	for (int y = 0; y < rows + 1; y++)
	{
		for (int x = 0; x < cols + 1; x++)
		{
			renderOperation->VertexBuffer->CreateVertex(x * grid_size , 0, -y * grid_size);
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
		}
	}
}
