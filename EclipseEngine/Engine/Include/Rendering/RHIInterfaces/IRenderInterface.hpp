#pragma once
#include "RHIInterfaces/Vertex.hpp"
#include "RHIInterfaces/IFlags.hpp"
#include "RHIInterfaces/IVertexArray.hpp"
#include "RHIInterfaces/IVertexBuffer.hpp"
#include "RHIInterfaces/IIndexBuffer.hpp"
#include "RHIInterfaces/IShaderProgram.hpp"
#include "RHIInterfaces/IVertexShader.hpp"
#include "RHIInterfaces/IFragmentShader.hpp"
#include "RHIInterfaces/ITexture2D.hpp"
#include "RHIInterfaces/ICubeMap.hpp"
#include "RHIInterfaces/IFrameBuffer.hpp"

namespace RHI
{
	class IRenderInterface
	{
	public:
		IRenderInterface() = default;
		virtual ~IRenderInterface() = default;

		virtual IVertexArray* InstantiateVertexArray() const = 0;
		virtual IVertexBuffer* InstantiateVertexBuffer() const = 0;
		virtual IIndexBuffer* InstantiateIndexBuffer() const = 0;
		virtual IShaderProgram* InstantiateShaderProgram() const = 0;
		virtual IVertexShader* InstantiateVertexShader() const = 0;
		virtual IFragmentShader* InstantiateFragmentShader() const = 0;
		virtual ITexture2D* InstantiateTexture2D() const = 0;
		virtual ICubeMap* InstantiateCubeMap() const = 0;
		virtual IFrameBuffer* InstantiateFrameBuffer() const = 0;

		virtual void DestroyVertexArray(IVertexArray* _vertexArray) const = 0;
		virtual void DestroyVertexBuffer(IVertexBuffer* _vertexBuffer) const = 0;
		virtual void DestroyIndexBuffer(IIndexBuffer* _indexBuffer) const = 0;
		virtual void DestroyShaderProgram(IShaderProgram* _shaderProgram) const = 0;
		virtual void DestroyVertexShader(IVertexShader* _vertexShader) const = 0;
		virtual void DestroyFragmentShader(IFragmentShader* _fragmentShader) const = 0;
		virtual void DestroyTexture2D(ITexture2D* _texture2D) const = 0;
		virtual void DestroyCubeMap(ICubeMap* _cubeMap) const = 0;
		virtual void DestroyFrameBuffer(IFrameBuffer* _frameBuffer) const = 0;

		virtual bool InitGraphicsAPI() const = 0;
		virtual void EnableContextCapability(IFLAGS _capability) const = 0;
		virtual void ClearBackgroundColor(Math::Vec4 _color) const = 0;
		virtual void ClearBuffer(IFLAGS _buffers) const = 0;
		virtual void Viewport(int _x, int _y, int _width, int _height) const = 0;
		virtual void DepthFunc(IFLAGS _depthComparison) const = 0;

	private:

	};
}