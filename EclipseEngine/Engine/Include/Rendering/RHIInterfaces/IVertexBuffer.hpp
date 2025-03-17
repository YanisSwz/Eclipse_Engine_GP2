#pragma once
#include "RHIInterfaces/Vertex.hpp"

namespace RHI
{
	class IVertexBuffer
	{
	public:
		IVertexBuffer() = default;
		virtual ~IVertexBuffer() = default;

		virtual void Init(Vertex* _vertices, size_t _size) = 0;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual void Delete() = 0;

	private:

	};
}