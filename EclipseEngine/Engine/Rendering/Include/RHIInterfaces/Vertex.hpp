#pragma once
#include "Maths.hpp"

namespace RHI
{
	struct Vertex
	{
		Math::Vec3 pos;
		Math::Vec2 textUV;
		Math::Vec3 normal;
	};
}