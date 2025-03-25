#pragma once
#include "Resource/IResource.hpp"
#include "RHIInterfaces/ITexture2D.hpp"

namespace Resource
{
	class Texture : public IResource
	{
	public:
		ECLIPSE_ENGINE Texture();
		ECLIPSE_ENGINE ~Texture() override;

		ECLIPSE_ENGINE void GetFileContent(std::string _path);
		ECLIPSE_ENGINE void Generate(RHI::IRenderInterface* _rdrInterface) override;
		
		ECLIPSE_ENGINE void Bind();
		ECLIPSE_ENGINE void Unbind();

		ECLIPSE_ENGINE void Delete();

	private:
		RHI::IRenderInterface* m_rdrInter = nullptr;

		RHI::ITexture2D* m_texture = nullptr;

		int m_width = 0;
		int m_height = 0;
		unsigned char* m_imgData = nullptr;
	};
}