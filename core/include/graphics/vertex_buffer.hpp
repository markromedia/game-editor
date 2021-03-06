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

#include <vector>
#include <iostream>

#define GLM_FORCE_RADIANS
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "vertex_data.hpp"
#include "opengl.h"

namespace graphics {
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
		void Init();
	protected:
		bool										buffers_created; 
	public:
		/// Members
        unsigned int                                flags;
		std::vector<float>							iva_data; // the actual data sent to OpenGL
		std::vector<GLushort>						indices_buffer;
		std::vector<Vertex*>						vertices; // ref of what's been allocated
        GLuint                                      vao_ptr;
		GLuint										iva_ptr;
		GLuint										indices_ptr;
		bool										do_update;   // indicates to buffer that it should update
		bool										data_is_dirty;
		unsigned long								max_vertices;
		unsigned long								max_indices;
		unsigned long								vertex_size;
		unsigned long								position_offset;
		unsigned long								texture_offset;
		unsigned long								color_offset;
		unsigned long								normal_offset;

		/// Constructor.	
		/// @param	flags			(optional) the flags.
		/// @param	max_vertices	(optional) the maximum vertices.
		VertexBuffer(unsigned int flags, int max_vertices, int max_indices);

        ///  binds this buffer and its data to the opengl context. Indices provided
        ///  are the opengl attrib indices. If not enabled value wouldn't matter. -1
        ///  is suggested for ignored ones
        /// @param	position_idx	Zero-based index of the position.
        /// @param	color_idx   	Zero-based index of the color.
        /// @param	normal_idx  	Zero-based index of the normal.
        /// @param	texture_idx 	Zero-based index of the texture.
        void Bind(int position_idx, int color_idx, int normal_idx, int texture_idx);

        /// unbinds this buffer and its data to the opengl context
        void Unbind();

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

		inline void normal(glm::vec3 vec)
		{
			this->n_x = vec.x;
			this->n_y = vec.y;
			this->n_z = vec.z;
		}
	};
}

#endif  // _VERTEX_BUFFER_hpp