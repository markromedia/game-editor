#include "graphics/vertex_buffer.hpp"

#include "graphics/vertex_data.hpp"
#include "graphics/gllogger.hpp"

using namespace Graphics;

VertexBuffer::VertexBuffer(unsigned int flags, int max_vertices, int max_indices) : flags(flags), max_vertices(max_vertices), max_indices(max_indices)
{
	this->Init();
}

void VertexBuffer::Init()
{
	vertex_size = POSITION_DATA_SIZE;
	position_offset = color_offset = texture_offset = 0; 
	data_is_dirty = true;
	do_update = true;
	buffers_created = false;
	int color_size = 0;
	int c_offset = POSITION_DATA_SIZE;

	if (USE_COLOR & flags)
	{
		vertex_size += COLOR_DATA_SIZE; 
		color_offset = c_offset; c_offset += COLOR_DATA_SIZE;
		color_size = COLOR_DATA_SIZE;
	}

	if (ONE_FLOAT_COLOR & flags)
	{
		vertex_size += ONE_FLOAT_COLOR_DATA_SIZE; 
		color_offset = c_offset;  c_offset += ONE_FLOAT_COLOR_DATA_SIZE;
		color_size = ONE_FLOAT_COLOR_DATA_SIZE;
	}

	if (USE_TEXTURE & flags) 
	{
		vertex_size += TEXTURE_COORDS_DATA_SIZE; 
		texture_offset = c_offset; c_offset += TEXTURE_COORDS_DATA_SIZE;
	}

	if (USE_NORMAL & flags) 
	{
		vertex_size += NORMAL_DATA_SIZE; 
		normal_offset = c_offset; c_offset += NORMAL_DATA_SIZE;
	}
	iva_data.reserve(max_vertices * (vertex_size /  sizeof(float))); //to prevent resizing and losing all of our pointers
}

void VertexBuffer::CreateBuffers()
{
	if (buffers_created)
	{
		return;
	}
    
    //create and bind the vbo
    glGenVertexArrays(1, &vao_ptr);
    glBindVertexArray(vao_ptr);
    
	glGenBuffers(1, &iva_ptr);
	glBindBuffer(GL_ARRAY_BUFFER, iva_ptr);
	glBufferData(GL_ARRAY_BUFFER, max_vertices * this->vertex_size, NULL, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	CHECK_GL_ERROR();
	
	if (!(DISABLE_IBO & flags))
	{
		glGenBuffers(1, &indices_ptr);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_ptr);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, max_indices * sizeof(GLushort), NULL, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		CHECK_GL_ERROR();
	}
    
    glBindVertexArray(0);

	buffers_created = true;
}

void VertexBuffer::UpdateBuffers() 
{
	if (data_is_dirty && do_update)
	{
		glBindBuffer(GL_ARRAY_BUFFER, iva_ptr);
		glBufferData(GL_ARRAY_BUFFER, max_vertices * this->vertex_size, NULL, GL_DYNAMIC_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, iva_data.size() *  sizeof(float), &iva_data[0]);
		CHECK_GL_ERROR();

		if (!(DISABLE_IBO & flags))
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indices_ptr);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, max_indices * sizeof(GLushort), NULL, GL_DYNAMIC_DRAW);
			glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, indices_buffer.size() * sizeof(GLushort), &indices_buffer[0]);
			CHECK_GL_ERROR();
		}

		data_is_dirty = false;
		do_update = false;
	}
}

Vertex* VertexBuffer::CreateVertex(float x, float y, float z) 
{
	if (vertices.size() >= max_vertices)
	{
		LOG_ERROR("Max vertices reached!");
		return NULL;
	}

	Vertex* v = new Vertex;
	//pos
	iva_data.push_back(x); v->x.Init(this, iva_data.back());
	iva_data.push_back(y); v->y.Init(this, iva_data.back());
	iva_data.push_back(z); v->z.Init(this, iva_data.back());

	if (USE_COLOR & flags)
	{
		iva_data.push_back(float()); v->r.Init(this, iva_data.back());
		iva_data.push_back(float()); v->g.Init(this, iva_data.back());
		iva_data.push_back(float()); v->b.Init(this, iva_data.back());
		iva_data.push_back(float()); v->a.Init(this, iva_data.back());
	}

	if (ONE_FLOAT_COLOR & flags)
	{
		iva_data.push_back(float()); v->a.Init(this, iva_data.back());
	}
	
	if (USE_TEXTURE & flags) 
	{
		iva_data.push_back(float()); v->s.Init(this, iva_data.back());
		iva_data.push_back(float()); v->t.Init(this, iva_data.back());
	}

	if (USE_NORMAL & flags) 
	{
		iva_data.push_back(float()); v->n_x.Init(this, iva_data.back());
		iva_data.push_back(float()); v->n_y.Init(this, iva_data.back());
		iva_data.push_back(float()); v->n_z.Init(this, iva_data.back());
	}

	vertices.push_back(v); // track the allocated vertices
	v->index = vertices.size() -1; //save the index for buffer index

	return v;
}

void VertexBuffer::CreateTriangle( Vertex* v1, Vertex* v2, Vertex* v3 )
{
	indices_buffer.push_back(v1->index);
	indices_buffer.push_back(v2->index);
	indices_buffer.push_back(v3->index);
}

void VertexBuffer::Bind(int position_idx, int color_idx, int normal_idx, int texture_idx) 
{
	//bind VAO
    glBindVertexArray(this->vao_ptr);
	//bind VBO
	glBindBuffer(GL_ARRAY_BUFFER, this->iva_ptr);
	
	//point to the vertices
	glEnableVertexAttribArray(position_idx);
	glVertexAttribPointer(position_idx, 3, GL_FLOAT, GL_FALSE, this->vertex_size, (const GLvoid*) this->position_offset);

	//point to color
	if (USE_COLOR & flags)
	{
		glEnableVertexAttribArray(color_idx);
		glVertexAttribPointer(color_idx, 4, GL_FLOAT, GL_FALSE, this->vertex_size , (const GLvoid*) this->color_offset);
	} else if (ONE_FLOAT_COLOR & flags)
	{
		glEnableVertexAttribArray(color_idx);
		glVertexAttribPointer(color_idx, 1, GL_FLOAT, GL_FALSE, this->vertex_size , (const GLvoid*) this->color_offset);
	}

	//point to normals
	if (USE_NORMAL & flags) 
	{
		glEnableVertexAttribArray(normal_idx);
		glVertexAttribPointer(normal_idx, 3, GL_FLOAT, GL_FALSE, this->vertex_size , (const GLvoid*) this->normal_offset);
	}
	
	//point to the texture
	if (USE_TEXTURE & flags) 
	{
		glEnableVertexAttribArray(texture_idx);
		glVertexAttribPointer(texture_idx, 2, GL_FLOAT, GL_FALSE, this->vertex_size , (const GLvoid*) this->texture_offset);
	}

	//bind the ibo
	if (!(DISABLE_IBO & flags))
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->indices_ptr);	
	}
}

void VertexBuffer::Unbind() {
	glBindVertexArray(0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}
