#pragma once
#include "ProjectExports.hpp"
#include "Component.hpp"
#include "Vec4.hpp"

namespace Core
{
	class ILight : public Component
	{
	public:
		ILight() = default;
		~ILight() = default;

		inline void SetColor(Math::Vec4 _color) { m_color = _color; };
		inline void SetColor(float _r, float _g, float _b, float _a) 
		{ 
			m_color.x = _r; 
			m_color.y = _g;
			m_color.z = _b;
			m_color.w = _a;
		};
		
	protected:
		Math::Vec4 m_color;
	};
}