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
        DEPTH_TEST = 6,
        BLEND = 7,
        SRC_ALPHA = 8,
        ONE_MINUS_SRC_ALPHA = 9,
        COUNT
	};

    inline int CastToOpenGLFlags(IFLAGS _type)
    {
        int typeIndex = static_cast<int>(_type);
        static const std::array<int, static_cast<int>(IFLAGS::COUNT)> openGLMacro =
        {
            GL_FLOAT,           // TYPE
            GL_COLOR_BUFFER_BIT, GL_DEPTH_BUFFER_BIT, GL_STENCIL_BUFFER_BIT,        // BUFFER_BIT
            GL_LESS, GL_LEQUAL,      // DEPTH_COMPARISON
            GL_DEPTH_TEST, 
            GL_BLEND, GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA
        };

        return openGLMacro[typeIndex];
    }
}