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
		inline Math::Vec4 GetColor() { return m_color; };
		
	protected:
		Math::Vec4 m_color;
	};
}