#pragma once
#include <glad/glad.h>
#include <array>

namespace RHI
{
	enum IFLAGS
	{
		TYPE_FLOAT = 1,
        COLOR_BUFFER_BIT = 2,
        DEPTH_BUFFER_BIT = 3,
        STENCIL_BUFFER_BIT = 4,
        DEPTH_LESS = 5,
        DEPTH_LEQUAL = 6
	};

    inline int CastToOpenGLFlags(IFLAGS _type)
    {
        int typeIndex = (int)_type;
        static const std::array<int, 6> openGLMacro =
        {
            GL_FLOAT,           // TYPE
            GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT, GL_STENCIL_BUFFER_BIT,        // BUFFER_BIT
            GL_LESS, GL_LEQUAL      // DEPTH_COMPARISON
        };

        return openGLMacro[typeIndex - 1];
    }
}