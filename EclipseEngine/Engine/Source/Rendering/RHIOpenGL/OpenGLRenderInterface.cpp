#include "RHIOpenGL/OpenGLRenderInterface.hpp"
#include "RHIOpenGL/OpenGLVertexArray.hpp"
#include "RHIOpenGL/OpenGLVertexBuffer.hpp"
#include "RHIOpenGL/OpenGLIndexBuffer.hpp"
#include "RHIOpenGL/OpenGLShaderProgram.hpp"
#include "RHIOpenGL/OpenGLVertexShader.hpp"
#include "RHIOpenGL/OpenGLFragmentShader.hpp"
#include "RHIOpenGL/OpenGLTexture2D.hpp"
#include "RHIOpenGL/OpenGLCubeMap.hpp"
#include "RHIOpenGL/OpenGLFrameBuffer.hpp"
#include "RHIOpenGL/OpenGLPipeline/OpenGLDefaultGraphicPipeline.hpp"
#include "RHIOpenGL/OpenGLRenderPass/OpenGLDeferredRenderPass.hpp"
#include <Glad/glad.h>
#include <iostream>
using namespace RHI::OpenGL;

RHI::IVertexArray* OpenGLRenderInterface::InstantiateVertexArray() const
{
	return new OpenGLVertexArray;
}

RHI::IVertexBuffer* OpenGLRenderInterface::InstantiateVertexBuffer() const
{
	return new OpenGLVertexBuffer;
}

RHI::IIndexBuffer* OpenGLRenderInterface::InstantiateIndexBuffer() const
{
	return new OpenGLIndexBuffer;
}

RHI::IShaderProgram* OpenGLRenderInterface::InstantiateShaderProgram() const
{
	return new OpenGLShaderProgram;
}

RHI::IVertexShader* OpenGLRenderInterface::InstantiateVertexShader() const
{
	return new OpenGLVertexShader;
}

RHI::IFragmentShader* OpenGLRenderInterface::InstantiateFragmentShader() const
{
	return new OpenGLFragmentShader;
}

RHI::ITexture2D* OpenGLRenderInterface::InstantiateTexture2D() const
{
	return new OpenGLTexture2D;
}

RHI::ICubeMap* OpenGLRenderInterface::InstantiateCubeMap() const
{
	return new OpenGLCubeMap;
}

RHI::IFrameBuffer* OpenGLRenderInterface::InstantiateFrameBuffer() const
{
	return new OpenGLFrameBuffer;
}

RHI::IGraphicPipeline* OpenGLRenderInterface::InstantiateDefaultGraphicPipeline() const
{
	return new OpenGLDefaultGraphicPipeline;
}

RHI::IRenderPass* OpenGLRenderInterface::InstantiateDeferredRenderPass() const
{
	return new OpenGLDeferredRenderPass;
}

void OpenGLRenderInterface::DestroyVertexArray(IVertexArray* _vertexArray) const
{
	if (!_vertexArray)
		return;
	delete _vertexArray;
}

void OpenGLRenderInterface::DestroyVertexBuffer(IVertexBuffer* _vertexBuffer) const
{
	if (!_vertexBuffer)
		return;
	delete _vertexBuffer;
}

void OpenGLRenderInterface::DestroyIndexBuffer(IIndexBuffer* _indexBuffer) const
{
	if (!_indexBuffer)
		return;
	delete _indexBuffer;
}

void OpenGLRenderInterface::DestroyShaderProgram(IShaderProgram* _shaderProgram) const
{
	if (!_shaderProgram)
		return;
	delete _shaderProgram;
}

void OpenGLRenderInterface::DestroyVertexShader(IVertexShader* _vertexShader) const
{
	if (!_vertexShader)
		return;
	delete _vertexShader;
}

void OpenGLRenderInterface::DestroyFragmentShader(IFragmentShader* _fragmentShader) const
{
	if (!_fragmentShader)
		return;
	delete _fragmentShader;
}

void OpenGLRenderInterface::DestroyTexture2D(ITexture2D* _texture2D) const
{
	if (!_texture2D)
		return;
	delete _texture2D;
}

void OpenGLRenderInterface::DestroyCubeMap(ICubeMap* _cubeMap) const
{
	if (!_cubeMap)
		return;
	delete _cubeMap;
}

void OpenGLRenderInterface::DestroyFrameBuffer(IFrameBuffer* _frameBuffer) const
{
	if (!_frameBuffer)
		return;
	delete _frameBuffer;
}

void OpenGLRenderInterface::DestroyDefaultGraphicPipeline(IGraphicPipeline* _graphicPipeline) const
{
	if (!_graphicPipeline)
		return;
	delete _graphicPipeline;
}

void OpenGLRenderInterface::DestroyDeferredRenderPass(IRenderPass* _renderPass) const
{
	if (!_renderPass)
		return;
	delete _renderPass;
}

bool OpenGLRenderInterface::InitGraphicsAPI() const
{
	if (!gladLoadGL())
	{
		std::cout << "Failed to load opengl function pointers!" << std::endl;
		return false;
	}
	return true;
}

void OpenGLRenderInterface::EnableContextCapability(IFLAGS _capability) const
{
	glEnable(CastToOpenGLFlags(_capability));
}

void OpenGLRenderInterface::ClearBackgroundColor(Math::Vec4 _color) const
{
	glClearColor(_color.x, _color.y, _color.z, _color.w);
}

void OpenGLRenderInterface::ClearBuffer(IFLAGS _buffers) const
{
	glClear(CastToOpenGLFlags(_buffers));
}

void OpenGLRenderInterface::Viewport(int _x, int _y, int _width, int _height) const
{
	glViewport(_x, _y, _width, _height);
}

void OpenGLRenderInterface::DepthFunc(IFLAGS _depthComparison) const
{
	glDepthFunc(CastToOpenGLFlags(_depthComparison));
}