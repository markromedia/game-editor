/// @file	src\graphics\vertex.hpp
///
/// Declares the vertex class
#ifndef _VERTEX_DATA_hpp
#define _VERTEX_DATA_hpp

namespace Graphics {
	//forward declarations
	class Vertex;
	class VertexBuffer;


	class VertexData
	{
		friend class Vertex;
		friend class VertexBuffer;
	protected:

		/// @summary	pointer to the parent who created this object.
		VertexBuffer* vertex_buffer;

		/// Default constructor.
		VertexData(void);

		/// Initialises this object.
		/// @param [in,out]	parent	If non-null, the parent.
		/// @param [in,out]	ptr   	If non-null, the pointer.
		void Init(VertexBuffer* parent, float& ptr);

		/// Determines if data is ok
		/// @return	true if it succeeds, false if it fails.
		bool CheckData();
	public:
		/// @summary	ref to the actual iva.
		float *iva_value;

		/// Gets the value.
		///
		/// @return	.
		float value();

		VertexData&			operator=  (float a);
		VertexData&			operator-= (float a);
		VertexData&			operator+= (float a);

	};

	inline float operator+ (VertexData& lhs, float rhs)
	{
		return *(lhs.iva_value) + rhs;
	}

	inline float operator- (VertexData& lhs, float rhs)
	{
		return *(lhs.iva_value) - rhs;
	}

	inline bool operator<(VertexData& lhs, float a)
	{
		return *(lhs.iva_value) < a;
	}

	inline bool operator> (VertexData& lhs, float a)
	{
		return *(lhs.iva_value) > a;
	}

	inline bool operator<= (VertexData& lhs, float a)
	{
		return *(lhs.iva_value) <= a;
	}

	inline bool operator>= (VertexData& lhs, float a)
	{
		return *(lhs.iva_value) >= a;
	}
}
#endif  // _VERTEX_DATA_hpp