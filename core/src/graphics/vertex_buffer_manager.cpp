#include "graphics/vertex_buffer_manager.hpp"

#include "graphics/vertex_buffer.hpp"

using namespace graphics;

VertexBufferManager* VertexBufferManager::instance = NULL;

VertexBufferManager::VertexBufferManager() 
{
	buffers.reserve(1024);
}

void VertexBufferManager::checkCreateInstance()
{
	if (VertexBufferManager::instance == NULL)
	{   
		VertexBufferManager::instance = new VertexBufferManager();
	}
}

VertexBuffer* VertexBufferManager::GetBuffer(int flags, int max_vertices, int max_indices)
{
	checkCreateInstance();

	VertexBuffer* v = new VertexBuffer(flags, max_vertices, max_indices);
	VertexBufferManager::instance->buffers.push_back(v);
	return VertexBufferManager::instance->buffers.back();
}


VertexBuffer* graphics::VertexBufferManager::GetBuffer( int flags /*= 0*/ )
{
	return 	graphics::VertexBufferManager::GetBuffer(flags, DEFAULT_MAX_INDICES, DEFAULT_MAX_INDICES);
}


void VertexBufferManager::CreateBuffers()
{
	//create all buffers
	for(std::vector<VertexBuffer*>::iterator it = VertexBufferManager::instance->buffers.begin(); it != VertexBufferManager::instance->buffers.end(); ++it) {
		(*it)->CreateBuffers();
	}
}

void VertexBufferManager::UpdateBuffers()
{
	//update all buffers
	for(std::vector<VertexBuffer*>::iterator it = VertexBufferManager::instance->buffers.begin(); it != VertexBufferManager::instance->buffers.end(); ++it) {
		(*it)->UpdateBuffers();
	}
}

