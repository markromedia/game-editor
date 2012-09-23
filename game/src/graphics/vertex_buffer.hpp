/// @file	src\graphics\vertex_buffer.hpp
///
/// Declares the render data class.
#ifndef _VERTEX_BUFFER_hpp
#define _VERTEX_BUFFER_hpp

//Flags
#define USE_COLOR				0x00000001				  //Use color index
#define USE_TEXTURE				0x00000002				  //Use texture index
#define USE_NORMAL				0x00000004				  //Use normals
#define ONE_FLOAT_COLOR			0x00000008				  //Use only a single float to store color info (in the "alpha" component)	
#define DISABLE_IBO				0x00000010				  //Disable the use of the IBO

#define POSITION_DATA_SIZE				3 * sizeof(float)
#define COLOR_DATA_SIZE					4 * sizeof(float)
#define TEXTURE_COORDS_DATA_SIZE		2 * sizeof(float)
#define NORMAL_DATA_SIZE				3 * sizeof(float)
#define ONE_FLOAT_COLOR_DATA_SIZE		1 * sizeof(float)

#include "../opengl.h"
#include <vector>
#include <iostream>
#include "vertex_data.hpp"

namespace Graphics {
	const int DEFAULT_MAX_VERTICES = 128;
	const int DEFAULT_MAX_INDICES = (DEFAULT_MAX_VERTICES / 4) * 6;

	class Vertex; //forward declaration
	class VertexBufferManager;

	///-----------------------------------------------------------------------------------------------
	class VertexBuffer
	{
	friend class VertexData;
	friend class VertexBufferManager;

	private:
		unsigned int flags;
		void Init();
	protected:
		bool										buffers_created; 
	public:
		/// Members
		std::vector<float>							iva_data; // the actual data sent to OpenGL
		std::vector<GLushort>						indices_buffer;
		std::vector<Vertex*>						vertices; // ref of what's been allocated
		GLuint										iva_ptr;
		GLuint										indices_ptr;
		bool										do_update;   // indicates to buffer that it should update
		bool										data_is_dirty;
		unsigned int								max_vertices;
		unsigned int								max_indices;
		unsigned int								vertex_size; 
		unsigned int								position_offset;
		unsigned int								texture_offset;
		unsigned int								color_offset;
		unsigned int								normal_offset;

		/// Constructor.	
		/// @param	flags			(optional) the flags.
		/// @param	max_vertices	(optional) the maximum vertices.
		VertexBuffer(unsigned int flags, int max_vertices, int max_indices);

		/// Creates the hardware buffers.
		void CreateBuffers();

		/// Updates the hardwares buffers.
		void UpdateBuffers();

		/// Creates a vertex.
		/// @param	x	(optional) the  float to process.
		/// @param	y	(optional) the  float to process.
		/// @param	z	(optional) the  float to process.
		/// @return	The new vertex.
		Vertex* CreateVertex(float x = 0, float y = 0, float z = 0); 

		/// Creates a triangle(in the indices array) of provided vertices. Add in order provided
		/// so need to make sure winding is ok
		/// @param	v1	The first Vertex.
		/// @param	v2	The second Vertex.
		/// @param	v3	The third Vertex.
		void CreateTriangle(Vertex* v1, Vertex* v2, Vertex* v3);
	};

	///-----------------------------------------------------------------------------------------------
	class Vertex
	{
	friend class VertexBuffer;
	protected:
		unsigned int index;
	public:
		VertexData x, y, z, r, g, b, a, s, t, n_x, n_y, n_z;

		inline void rgba(float r, float g, float b, float a = 1)
		{
			this->r = r;
			this->g = g;
			this->b = b;
			this->a = a;
		}

		inline void normal(float n_x, float n_y, float n_z)
		{
			this->n_x = n_x;
			this->n_y = n_y;
			this->n_z = n_z;
		}
	};
}

#endif  // _VERTEX_BUFFER_hpp