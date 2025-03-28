#pragma once
#include "IResource.hpp"

namespace Resource
{
	class VertShader : public IResource
	{
	public:
		ECLIPSE_ENGINE VertShader();
		ECLIPSE_ENGINE ~VertShader() override;

		ECLIPSE_ENGINE void GetContentFile(std::string _path);
		ECLIPSE_ENGINE void Generate(RHI::IRenderInterface* _rdrInterface) override;

		ECLIPSE_ENGINE unsigned int GetID() const;

		ECLIPSE_ENGINE void Delete() override;

	private:
		RHI::IRenderInterface* m_rdrInter = nullptr;

		std::string m_vertexFileContent = "";
		RHI::IVertexShader* m_vertexShader = nullptr;
	};
}