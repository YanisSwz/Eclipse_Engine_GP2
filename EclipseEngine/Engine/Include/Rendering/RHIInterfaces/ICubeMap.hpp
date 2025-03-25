#pragma once
#include "Resource/TextureExtention.hpp"
#include <vector>
#include <string>

namespace RHI
{
	class ICubeMap
	{
	public:
		ICubeMap() = default;
		 virtual ~ICubeMap() = default;

		virtual void Generate(std::vector<unsigned char*> _data, int _width, int _height, Resource::TEXTURE_EXTENSION _textureExtention) = 0;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual void Delete() = 0;

	private:

	};
}