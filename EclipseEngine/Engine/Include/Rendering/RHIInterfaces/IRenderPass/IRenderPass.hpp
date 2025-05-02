#pragma once

namespace Math
{
	class Mat4;
}

namespace RHI
{
	class IRenderInterface;

	class IRenderPass
	{
	public:
		IRenderPass() = default;
		virtual ~IRenderPass() = default;

		virtual void Init(int _width, int _height) = 0;
		virtual void Rescale(int _width, int _height) = 0;
		inline int GetWidth() const { return m_width; }
		inline int GetHeight() const { return m_height; }
		virtual void Delete() = 0;

	protected:
		int m_width = 0;
		int m_height = 0;
	};
}