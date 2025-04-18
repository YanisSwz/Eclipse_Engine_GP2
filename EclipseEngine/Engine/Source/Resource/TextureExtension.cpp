#include "Resource/TextureExtension.hpp"

namespace Resource
{
	const char* TEXTURE_EXTENSION_TO_STR(TEXTURE_EXTENSION _textureExtension)
	{
		switch (_textureExtension)
		{
		case TEXTURE_EXTENSION::PNG:
			return ".png";
		case TEXTURE_EXTENSION::JPG:
			return ".jpg";
		default:
			return "";
		}
	}
}