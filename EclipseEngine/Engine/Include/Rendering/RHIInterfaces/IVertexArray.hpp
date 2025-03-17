#pragma once
#include "RHIInterfaces/Vertex.hpp"
#include "IFlags.hpp"

namespace RHI
{
	class IVertexBuffer;

	class IVertexArray
	{
	public:
		IVertexArray() = default;
		virtual ~IVertexArray() = default;

		virtual void Init() = 0;
		virtual void LinkVertexBuffer(IVertexBuffer& _vertexBuffer, int _layout, int numComponents, IFLAGS _type, size_t _stride, void* _offset) = 0;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual void Delete() = 0;

	private:

	};
}