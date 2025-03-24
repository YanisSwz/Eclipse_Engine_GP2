#include "RHIOpenGL/OpenGLFrameBuffer.hpp"
#include <iostream>
using namespace RHI::OpenGL;

OpenGLFrameBuffer::~OpenGLFrameBuffer()
{
	Delete();
}

void OpenGLFrameBuffer::Init(int _width, int _height)
{
	width = _width;
	height = _height;

	glGenFramebuffers(1, &m_fboID);
	glBindFramebuffer(GL_FRAMEBUFFER, m_fboID);

	glGenTextures(1, &m_textID);
	glBindTexture(GL_TEXTURE_2D, m_textID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textID, 0);

	glGenRenderbuffers(1, &m_rboID);
	glBindRenderbuffer(GL_RENDERBUFFER, m_rboID);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rboID);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!\n";

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glBindTexture(GL_TEXTURE_2D, 0);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void OpenGLFrameBuffer::Rescale(int _width, int _height)
{
	width = _width;
	height = _height;

	glBindTexture(GL_TEXTURE_2D, m_textID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, _width, _height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_textID, 0);

	glBindRenderbuffer(GL_RENDERBUFFER, m_rboID);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, _width, _height);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_rboID);
}

void OpenGLFrameBuffer::Bind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_fboID);
}

void OpenGLFrameBuffer::Unbind()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

unsigned int OpenGLFrameBuffer::GetTextureID() const
{
	return m_textID;
}

void OpenGLFrameBuffer::Delete()
{
	glDeleteTextures(1, &m_textID);
	glDeleteFramebuffers(1, &m_fboID);
	glDeleteRenderbuffers(1, &m_rboID);
}