#pragma once
#include "Resource/IGraphicsResource.hpp"
#include "RHIInterfaces/ITexture2D.hpp"

namespace Resource
{
	class Texture : public IGraphicsResource
	{
	public:
		ECLIPSE_ENGINE Texture(std::string _name = "");
		ECLIPSE_ENGINE ~Texture() override;

		ECLIPSE_ENGINE void GetFileContent(std::string _path) override;
		ECLIPSE_ENGINE void Generate(RHI::IRenderInterface* _rdrInterface) override;
		
		ECLIPSE_ENGINE unsigned int GetID() const;
		ECLIPSE_ENGINE void Bind();
		ECLIPSE_ENGINE void Unbind();

		ECLIPSE_ENGINE void Delete() override;

	private:
		RHI::IRenderInterface* m_rdrInter = nullptr;

		RHI::ITexture2D* m_texture = nullptr;

		int m_width = 0;
		int m_height = 0;
		int m_numColCh = 0;
		unsigned char* m_imgData = nullptr;
	};
}