#include "graphics/vertex_data.hpp"

#include "graphics/vertex_buffer.hpp"
#include "logger.hpp"

using namespace graphics;

VertexData::VertexData(void)
{
	vertex_buffer = NULL;
	iva_value = NULL;
}

void VertexData::Init(VertexBuffer* parent, float& ptr)
{
	vertex_buffer = parent;
	iva_value = &ptr;
}

bool VertexData::CheckData()
{
	if (vertex_buffer == NULL && iva_value == NULL) 
	{
		LOG_WARNING("Attempting to set VertexData not bound to an IVA");
		return false;
	}
	return true;
}

float VertexData::value() 
{
	return *iva_value;
}

VertexData& VertexData::operator= (float a)
{
	if (!CheckData()) return *this;
	if (*iva_value != a)
	{
		*iva_value = a;
		vertex_buffer->data_is_dirty = true;
	}
	return *this;
}

VertexData& VertexData::operator-= (float a)
{
	if (!CheckData()) return *this;
	*iva_value -= a;
	vertex_buffer->data_is_dirty = true;
	return *this;
}

VertexData& VertexData::operator+= (float a)
{
	if (!CheckData()) return *this;
	*iva_value += a;
	vertex_buffer->data_is_dirty = true;
	return *this;
}




