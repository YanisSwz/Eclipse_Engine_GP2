#pragma once
#include "IResource.hpp"

namespace Resource
{
	class FragShader : public IResource
	{
	public:
		ECLIPSE_ENGINE FragShader(std::string _name = "");
		ECLIPSE_ENGINE ~FragShader() override;

		ECLIPSE_ENGINE void GetFileContent(std::string _path) override;
		ECLIPSE_ENGINE void Generate(RHI::IRenderInterface* _rdrInterface) override;

		ECLIPSE_ENGINE unsigned int GetID() const;

		ECLIPSE_ENGINE void Delete() override;

	private:
		RHI::IRenderInterface* m_rdrInter = nullptr;
		
		std::string m_fragmentFileContent = "";
		RHI::IFragmentShader* m_fragmentShader = nullptr;
	};
}