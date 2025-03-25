#include "Resource/TextureExtention.hpp"

namespace Resource
{
	const char* TEXTURE_EXTENTION_TO_STR(TEXTURE_EXTENSION _textureExtention)
	{
		switch (_textureExtention)
		{
		case TEXTURE_EXTENSION::PNG:
			return ".png";
			break;
		case TEXTURE_EXTENSION::JPG:
			return ".jpg";
			break;
		}
		return "";
	}
}