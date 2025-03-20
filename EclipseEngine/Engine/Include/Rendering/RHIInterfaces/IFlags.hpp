#pragma once
#include <glad/glad.h>
#include <array>

namespace RHI
{
    enum class IFLAGS : int
    {
        TYPE_FLOAT = 0,
        COLOR_BUFFER_BIT = 1,
        DEPTH_BUFFER_BIT = 2,
        STENCIL_BUFFER_BIT = 3,
        DEPTH_LESS = 4,
        DEPTH_LEQUAL = 5,
        COUNT
	};

    inline int CastToOpenGLFlags(IFLAGS _type)
    {
        int typeIndex = static_cast<int>(_type);
        static const std::array<int, static_cast<int>(IFLAGS::COUNT)> openGLMacro =
        {
            GL_FLOAT,           // TYPE
            GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT, GL_STENCIL_BUFFER_BIT,        // BUFFER_BIT
            GL_LESS, GL_LEQUAL      // DEPTH_COMPARISON
        };

        return openGLMacro[typeIndex];
    }
}