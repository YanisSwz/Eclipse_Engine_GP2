#pragma once
#include "Vertex.hpp"
#include <vector>

namespace RHI
{
	class IVertexArray;

	class IIndexBuffer
	{
	public:
		IIndexBuffer() = default;
		virtual ~IIndexBuffer() = default;

		virtual void Init(unsigned int* _indices, size_t _size) = 0;
		virtual void Draw(IVertexArray* _vertexArray) = 0;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual void Delete() = 0;

	protected:
		std::vector<uint32_t> indexBuffer;

	};
}