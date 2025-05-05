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
		inline Math::Vec4 GetColor() const { return m_color; };
		inline Math::Vec4& GetColorRef() { return m_color; };

		virtual void Serialize(json& _j) override = 0;
		virtual void Deserialize(const json& _j) override = 0;
		
	protected:
		Math::Vec4 m_color;
	};
}