#pragma once
#include "RHIInterfaces/IRenderInterface.hpp"
#include "RHIOpenGL/OpenGLVertexArray.hpp"
#include "RHIOpenGL/OpenGLVertexBuffer.hpp"
#include "RHIOpenGL/OpenGLIndexBuffer.hpp"
#include "RHIOpenGL/OpenGLShaderProgram.hpp"
#include "RHIOpenGL/OpenGLVertexShader.hpp"
#include "RHIOpenGL/OpenGLFragmentShader.hpp"
#include "RHIOpenGL/OpenGLTexture2D.hpp"
#include "RHIOpenGL/OpenGLCubeMap.hpp"
#include "RHIOpenGL/OpenGLFrameBuffer.hpp"

namespace RHI
{
	namespace OpenGL
	{
		class OpenGLRenderInterface : public IRenderInterface
		{
		public:
			OpenGLRenderInterface() = default;
			~OpenGLRenderInterface() override = default;

			IVertexArray* InstantiateVertexArray() const override;
			IVertexBuffer* InstantiateVertexBuffer() const override;
			IIndexBuffer* InstantiateIndexBuffer() const override;
			IShaderProgram* InstantiateShaderProgram() const override;
			IVertexShader* InstantiateVertexShader() const override;
			IFragmentShader* InstantiateFragmentShader() const override;
			ITexture2D* InstantiateTexture2D() const override;
			ICubeMap* InstantiateCubeMap() const override;
			IFrameBuffer* InstantiateFrameBuffer() const override;

			void DestroyVertexArray(IVertexArray* _vertexArray) const override;
			void DestroyVertexBuffer(IVertexBuffer* _vertexBuffer) const override;
			void DestroyIndexBuffer(IIndexBuffer* _indexBuffer) const override;
			void DestroyShaderProgram(IShaderProgram* _shaderProgram) const override;
			void DestroyVertexShader(IVertexShader* _vertexShader) const override;
			void DestroyFragmentShader(IFragmentShader* _fragmentShader) const override;
			void DestroyTexture2D(ITexture2D* _texture2D) const override;
			void DestroyCubeMap(ICubeMap* _cubeMap) const override;
			void DestroyFrameBuffer(IFrameBuffer* _frameBuffer) const override;

			bool InitGraphicsAPI() const override;
			void EnableContextCapability(IFLAGS _capability) const override;
			void ClearBackgroundColor(Math::Vec4 _color) const override;
			void ClearBuffer(IFLAGS _buffers) const override;
			void Viewport(int _x, int _y, int _width, int _height) const override;
			void DepthFunc(IFLAGS _depthComparison) const override;

		private:

		};
	}
}