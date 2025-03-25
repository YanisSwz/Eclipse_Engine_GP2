#pragma once
#include <string>

namespace RHI
{
	class ITexture2D
	{
	public:
		ITexture2D() = default;
		virtual ~ITexture2D() = default;

		virtual void Generate(unsigned char* _data, int _width, int _height) = 0;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual unsigned int GetID() const = 0;
		virtual void Delete() = 0;
	private:

	};
}