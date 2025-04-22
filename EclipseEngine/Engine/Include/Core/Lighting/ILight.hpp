#pragma once
#include "ProjectExports.hpp"
#include "Component.hpp"
#include "Vec3.hpp"

namespace Core
{
	class ILight : public Component
	{
	public:
		ILight() = default;
		~ILight() = default;
		
	protected:
		Math::Vec3 m_color;
	};
}