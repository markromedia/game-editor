#ifndef __COLOR4F_hpp
#define __COLOR4F_hpp

namespace Graphics {
	class Color4f
	{
	public:
		/// Constructor.
		/// @param	r	(optional) the  float to process.
		/// @param	g	(optional) the  float to process.
		/// @param	b	(optional) the  float to process.
		/// @param	a	(optional) the  float to process.
		Color4f(float r = 1, float g = 1, float b = 1, float a = 1);

		/// the individual color components
		float r, g, b, a;

		/// Convience name
		/// @param	r	The float to process.
		/// @param	g	The float to process.
		/// @param	b	The float to process.
		/// @param	a	The float to process.
		void rbga(float r, float g, float b, float a);

		//////////////////////////////////////////////////////////////////////////
		///							PRE-DEFINED COLORS						   ///
		//////////////////////////////////////////////////////////////////////////
		static Color4f WHITE;

		static Color4f BLACK;
	};
}
#endif  // __COLOR4F_hpp