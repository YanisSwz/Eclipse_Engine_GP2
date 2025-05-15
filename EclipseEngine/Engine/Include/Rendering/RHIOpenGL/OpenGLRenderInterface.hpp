#pragma once
#include "RHIInterfaces/IRenderInterface.hpp"
#include "ProjectExports.hpp"

namespace RHI
{
	namespace OpenGL
	{
		class OpenGLRenderInterface : public IRenderInterface
		{
		public:
			ECLIPSE_ENGINE OpenGLRenderInterface() = default;
			ECLIPSE_ENGINE ~OpenGLRenderInterface() override = default;

			ECLIPSE_ENGINE IVertexArray* InstantiateVertexArray() const override;
			ECLIPSE_ENGINE IVertexBuffer* InstantiateVertexBuffer() const override;
			ECLIPSE_ENGINE IIndexBuffer* InstantiateIndexBuffer() const override;
			ECLIPSE_ENGINE IShaderProgram* InstantiateShaderProgram() const override;
			ECLIPSE_ENGINE IVertexShader* InstantiateVertexShader() const override;
			ECLIPSE_ENGINE IGeometryShader* InstantiateGeometryShader() const override;
			ECLIPSE_ENGINE IFragmentShader* InstantiateFragmentShader() const override;
			ECLIPSE_ENGINE ITexture2D* InstantiateTexture2D() const override;
			ECLIPSE_ENGINE ICubeMap* InstantiateCubeMap() const override;
			ECLIPSE_ENGINE IFrameBuffer* InstantiateFrameBuffer() const override;
			ECLIPSE_ENGINE IGraphicPipeline* InstantiateDefaultGraphicPipeline() const override;
			ECLIPSE_ENGINE IRenderPass* InstantiateDeferredRenderPass() const override;

			ECLIPSE_ENGINE void DestroyVertexArray(IVertexArray* _vertexArray) const override;
			ECLIPSE_ENGINE void DestroyVertexBuffer(IVertexBuffer* _vertexBuffer) const override;
			ECLIPSE_ENGINE void DestroyIndexBuffer(IIndexBuffer* _indexBuffer) const override;
			ECLIPSE_ENGINE void DestroyShaderProgram(IShaderProgram* _shaderProgram) const override;
			ECLIPSE_ENGINE void DestroyVertexShader(IVertexShader* _vertexShader) const override;
			ECLIPSE_ENGINE void DestroyGeometryShader(IGeometryShader* _geometryShader) const override;
			ECLIPSE_ENGINE void DestroyFragmentShader(IFragmentShader* _fragmentShader) const override;
			ECLIPSE_ENGINE void DestroyTexture2D(ITexture2D* _texture2D) const override;
			ECLIPSE_ENGINE void DestroyCubeMap(ICubeMap* _cubeMap) const override;
			ECLIPSE_ENGINE void DestroyFrameBuffer(IFrameBuffer* _frameBuffer) const override;
			ECLIPSE_ENGINE void DestroyDefaultGraphicPipeline(IGraphicPipeline* _graphicPipeline) const override;
			ECLIPSE_ENGINE void DestroyDeferredRenderPass(IRenderPass* _renderPass) const override;

			ECLIPSE_ENGINE bool InitGraphicsAPI() const override;
			ECLIPSE_ENGINE void EnableContextCapability(IFLAGS _capability) const override;
			ECLIPSE_ENGINE void DisableContextCapability(IFLAGS _capability) const override;
			ECLIPSE_ENGINE void ClearBackgroundColor(Math::Vec4 _color) const override;
			ECLIPSE_ENGINE void ClearBuffer(IFLAGS _buffers) const override;
			ECLIPSE_ENGINE void Viewport(int _x, int _y, int _width, int _height) const override;
			ECLIPSE_ENGINE void DepthFunc(IFLAGS _depthComparison) const override;
			ECLIPSE_ENGINE void BlendFunc(IFLAGS _sFactor, IFLAGS _dFactor) const override;
		};
	}
}