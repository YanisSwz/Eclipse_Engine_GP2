#pragma once
#include "IGraphicsResource.hpp"

namespace Resource
{
	class GeoShader : public IGraphicsResource
	{
	public:
		ECLIPSE_ENGINE GeoShader(std::string _name = "");
		ECLIPSE_ENGINE ~GeoShader() override;

		ECLIPSE_ENGINE void GetFileContent(std::string _path) override;
		ECLIPSE_ENGINE void Generate(RHI::IRenderInterface* _rdrInterface) override;

		ECLIPSE_ENGINE unsigned int GetID() const;

		ECLIPSE_ENGINE void Delete() override;

	private:
		RHI::IRenderInterface* m_rdrInter = nullptr;

		std::string m_geometryFileContent = "";
		RHI::IGeometryShader* m_geometryShader = nullptr;
	};
}