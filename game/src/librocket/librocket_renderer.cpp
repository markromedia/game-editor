/*
 * This source file is part of libRocket, the HTML/CSS Interface Middleware
 *
 * For the latest information, see http://www.librocket.com
 *
 * Copyright (c) 2008-2010 CodePoint Ltd, Shift Technology Ltd
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#include "librocket_renderer.hpp"
#include <Rocket/Core.h>

#include "../game.hpp"

#define GL_CLAMP_TO_EDGE 0x812F

LibRocketRenderer::LibRocketRenderer()
{
	this->inited = false;
}

void LibRocketRenderer::Init(int num_vertices)
{
	GLint linked;

	//create buffer to draw to
	vertex_buff = new Graphics::VertexBuffer(USE_COLOR | USE_TEXTURE, 1024, 1536);
	vertex_buff->CreateBuffers();
	CHECK_GL_ERROR();

	//create the shaders
	ShaderObject* fragmentShader = ShaderManager::CreateShader(GL_FRAGMENT_SHADER, "resources\\rocket\\lib_rocket.frag");
	ShaderObject* vertexShader = ShaderManager::CreateShader(GL_VERTEX_SHADER, "resources\\rocket\\lib_rocket.vert");
	CHECK_GL_ERROR();

	programObject = glCreateProgram();

	//attach shaders and link program
	glAttachShader(programObject, vertexShader->id);
	glAttachShader(programObject, fragmentShader->id);
	CHECK_GL_ERROR();

	glBindAttribLocation(programObject, 0, "a_position");
	glBindAttribLocation(programObject, 1, "a_color");
	glBindAttribLocation(programObject, 2, "a_texCoord");

	glAttachShader(programObject, fragmentShader->id);

	glLinkProgram(programObject);

	glGetProgramiv(programObject, GL_LINK_STATUS, &linked);
	if (!linked) 
	{
		CHECK_GL_PROGRAM_ERROR(programObject);
		glDeleteProgram(programObject);
	}

	//get a handle for the uniforms
	mvp_matrix_uniform = glGetUniformLocation(programObject, "u_mvp");
	texture_sampler_uniform = glGetUniformLocation(programObject, "s_texture");
	alpha_uniform = glGetUniformLocation(programObject, "u_alpha");

	//set up inverse y-matrix 
	y_inverse_matrix.LoadIdentity();
	y_inverse_matrix.data[5] = -1;

	inited = true;
}

// Called by Rocket when it wants to render geometry that it does not wish to optimise.
void LibRocketRenderer::RenderGeometry(Rocket::Core::Vertex* vertices, int num_vertices, int* indices, int num_indices, const Rocket::Core::TextureHandle texture, const Rocket::Core::Vector2f& translation)
{
	if (!inited)
	{
		Init(num_vertices);
	}

	//update VBO
	vertex_buff->iva_data.clear();
	for (int i = 0; i < num_vertices; i++) 
	{
		vertex_buff->iva_data.push_back(vertices[i].position.x);
		vertex_buff->iva_data.push_back(vertices[i].position.y);
		vertex_buff->iva_data.push_back(0);
		vertex_buff->iva_data.push_back(vertices[i].colour.red / 255.0f);
		vertex_buff->iva_data.push_back(vertices[i].colour.green / 255.0f);
		vertex_buff->iva_data.push_back(vertices[i].colour.blue / 255.0f);
		vertex_buff->iva_data.push_back(vertices[i].colour.alpha / 255.0f);
		if (texture)
		{
			vertex_buff->iva_data.push_back(vertices[i].tex_coord.x);
			vertex_buff->iva_data.push_back(vertices[i].tex_coord.y);
		}
		else
		{
			vertex_buff->iva_data.push_back(0);
			vertex_buff->iva_data.push_back(0);
		}
	}

	//update IBO
	vertex_buff->indices_buffer.clear();
	for (int i = 0; i < num_indices; i++)
	{
		vertex_buff->indices_buffer.push_back((GLushort) indices[i]);
	}
	
	//send data to openGL
	vertex_buff->data_is_dirty = true;
	vertex_buff->do_update = true;
	vertex_buff->UpdateBuffers();

	// attach librocket program
	glUseProgram(this->programObject);

	// set required blend states
	GLState::Enable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//set up matrices
	model_view_mat.SetTranslation(translation.x, translation.y, 0);
	model_view_projection_mat.SetOrthoProjection(Constants::SCREEN_WIDTH, Constants::SCREEN_HEIGHT);
	model_view_projection_mat = y_inverse_matrix * model_view_projection_mat * model_view_mat;

	// Set the sampler texture unit to 0
	glActiveTexture(GL_TEXTURE0);
	glUniform1i(texture_sampler_uniform, 0);

	// pass the mvp matrix to the shader
	glUniformMatrix4fv(mvp_matrix_uniform, 1, 0, &model_view_projection_mat.data[0]);

	// bind the iva
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buff->iva_ptr);
	
	// point to the vertices
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, vertex_buff->vertex_size, (const GLvoid*) vertex_buff->position_offset);

	// point to the color
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, vertex_buff->vertex_size, (const GLvoid*) vertex_buff->color_offset);

	if (!texture)
	{
		glDisableVertexAttribArray(2);
	}
	else
	{
		// enable texture2d
		glBindTexture(GL_TEXTURE_2D, (GLuint) texture);
		// bind texture coordinates to attribute
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, vertex_buff->vertex_size, (const GLvoid*) vertex_buff->texture_offset);
	}

	// bind ibo/draw
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vertex_buff->indices_ptr);
	glDrawElements(GL_TRIANGLES, vertex_buff->indices_buffer.size(), GL_UNSIGNED_SHORT, 0);

	CHECK_GL_ERROR();
	
}

// Called by Rocket when it wants to compile geometry it believes will be static for the forseeable future.		
Rocket::Core::CompiledGeometryHandle LibRocketRenderer::CompileGeometry(Rocket::Core::Vertex* ROCKET_UNUSED(vertices), int ROCKET_UNUSED(num_vertices), int* ROCKET_UNUSED(indices), int ROCKET_UNUSED(num_indices), const Rocket::Core::TextureHandle ROCKET_UNUSED(texture))
{
	return (Rocket::Core::CompiledGeometryHandle) NULL;
}

// Called by Rocket when it wants to render application-compiled geometry.		
void LibRocketRenderer::RenderCompiledGeometry(Rocket::Core::CompiledGeometryHandle ROCKET_UNUSED(geometry), const Rocket::Core::Vector2f& ROCKET_UNUSED(translation))
{
}

// Called by Rocket when it wants to release application-compiled geometry.		
void LibRocketRenderer::ReleaseCompiledGeometry(Rocket::Core::CompiledGeometryHandle ROCKET_UNUSED(geometry))
{
}

// Called by Rocket when it wants to enable or disable scissoring to clip content.		
void LibRocketRenderer::EnableScissorRegion(bool enable)
{
	if (enable)
		GLState::Enable(GL_SCISSOR_TEST);
	else
		GLState::Disable(GL_SCISSOR_TEST);
	CHECK_GL_ERROR();
}

// Called by Rocket when it wants to change the scissor region.		
void LibRocketRenderer::SetScissorRegion(int x, int y, int width, int height)
{
	glScissor(x, 768 - (y + height), width, height);
}

// Set to byte packing, or the compiler will expand our struct, which means it won't read correctly from file
#pragma pack(1) 
struct TGAHeader 
{
	char  idLength;
	char  colourMapType;
	char  dataType;
	short int colourMapOrigin;
	short int colourMapLength;
	char  colourMapDepth;
	short int xOrigin;
	short int yOrigin;
	short int width;
	short int height;
	char  bitsPerPixel;
	char  imageDescriptor;
};
// Restore packing
#pragma pack()

// Called by Rocket when a texture is required by the library.		
bool LibRocketRenderer::LoadTexture(Rocket::Core::TextureHandle& texture_handle, Rocket::Core::Vector2i& texture_dimensions, const Rocket::Core::String& source)
{
	Rocket::Core::FileInterface* file_interface = Rocket::Core::GetFileInterface();
	Rocket::Core::FileHandle file_handle = file_interface->Open(source);
	if (!file_handle)
	{
		return false;
	}
	
	file_interface->Seek(file_handle, 0, SEEK_END);
	size_t buffer_size = file_interface->Tell(file_handle);
	file_interface->Seek(file_handle, 0, SEEK_SET);
	
	char* buffer = new char[buffer_size];
	file_interface->Read(buffer, buffer_size, file_handle);
	file_interface->Close(file_handle);

	TGAHeader header;
	memcpy(&header, buffer, sizeof(TGAHeader));
	
	int color_mode = header.bitsPerPixel / 8;
	int image_size = header.width * header.height * 4; // We always make 32bit textures 
	
	if (header.dataType != 2)
	{
		Rocket::Core::Log::Message(Rocket::Core::Log::LT_ERROR, "Only 24/32bit uncompressed TGAs are supported.");
		return false;
	}
	
	// Ensure we have at least 3 colors
	if (color_mode < 3)
	{
		Rocket::Core::Log::Message(Rocket::Core::Log::LT_ERROR, "Only 24 and 32bit textures are supported");
		return false;
	}
	
	const char* image_src = buffer + sizeof(TGAHeader);
	unsigned char* image_dest = new unsigned char[image_size];
	
	// Targa is BGR, swap to RGB and flip Y axis
	for (long y = 0; y < header.height; y++)
	{
		long read_index = y * header.width * color_mode;
		long write_index = ((header.imageDescriptor & 32) != 0) ? read_index : (header.height - y - 1) * header.width * color_mode;
		for (long x = 0; x < header.width; x++)
		{
			image_dest[write_index] = image_src[read_index+2];
			image_dest[write_index+1] = image_src[read_index+1];
			image_dest[write_index+2] = image_src[read_index];
			if (color_mode == 4)
				image_dest[write_index+3] = image_src[read_index+3];
			else
				image_dest[write_index+3] = 255;
			
			write_index += 4;
			read_index += color_mode;
		}
	}

	texture_dimensions.x = header.width;
	texture_dimensions.y = header.height;
	
	bool success = GenerateTexture(texture_handle, image_dest, texture_dimensions);
	
	delete [] image_dest;
	delete [] buffer;
	
	return success;
}

// Called by Rocket when a texture is required to be built from an internally-generated sequence of pixels.
bool LibRocketRenderer::GenerateTexture(Rocket::Core::TextureHandle& texture_handle, const Rocket::Core::byte* source, const Rocket::Core::Vector2i& source_dimensions)
{
	GLuint texture_id = 0;
	glGenTextures(1, &texture_id);
	if (texture_id == 0)
	{
		printf("Failed to generate textures\n");
		return false;
	}

	glBindTexture(GL_TEXTURE_2D, texture_id);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, source_dimensions.x, source_dimensions.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, source);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	texture_handle = (Rocket::Core::TextureHandle) texture_id;

	return true;
}

// Called by Rocket when a loaded texture is no longer required.		
void LibRocketRenderer::ReleaseTexture(Rocket::Core::TextureHandle texture_handle)
{
	glDeleteTextures(1, (GLuint*) &texture_handle);
}

