#pragma once

namespace RHI
{
	class IFrameBuffer
	{
	public:
		IFrameBuffer() = default;
		virtual ~IFrameBuffer() = default;

		int width = 0;
		int height = 0;

		virtual void Init(int _width, int _height) = 0;
		virtual void Rescale(int _width, int _height) = 0;
		virtual void Bind() = 0;
		virtual void Unbind() = 0;
		virtual unsigned int GetTextureID() const = 0;
		virtual unsigned int GetFrameBufferID() const = 0;
		virtual unsigned int GetDepthBufferID() const = 0;
		virtual void Delete() = 0;

	private:

	};
}