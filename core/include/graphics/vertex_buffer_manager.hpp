#ifndef __VERTEX_BUFFER_MANAGER_hpp
#define __VERTEX_BUFFER_MANAGER_hpp

#include <vector>

#include "vertex_buffer.hpp"

namespace graphics {
	class VertexBufferManager {
	private:
		/// @summary	The instance.
		static VertexBufferManager* instance;

		/// Check create instance.
		static void checkCreateInstance();

		/// @summary	The buffers.
		std::vector<VertexBuffer*> buffers;

		/// Default constructor.
		VertexBufferManager(void);
	public:
		static VertexBuffer* GetBuffer(int flags, int max_vertices, int max_indices);

		static VertexBuffer* GetBuffer(int flags = 0);

		/// Creates all the uninitialized buffers
		static void CreateBuffers();

		/// Updates all the dirty buffers marked for updating
		static void UpdateBuffers();
	};
}

#endif  // __VERTEX_BUFFER_MANAGER_hpp