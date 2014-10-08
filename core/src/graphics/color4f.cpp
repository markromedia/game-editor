#include "graphics/color4f.hpp"

using namespace Graphics;

Color4f::Color4f(float r, float g, float b, float a) : r(r), g(g), b(b), a(a)
{
}



void Graphics::Color4f::rbga( float r, float g, float b, float a )
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

//////////////////////////////////////////////////////////////////////////
///							PRE-DEFINED COLORS						   ///
//////////////////////////////////////////////////////////////////////////
Color4f Color4f::WHITE = Color4f(1, 1, 1);

Color4f Color4f::BLACK = Color4f(0, 0, 0);