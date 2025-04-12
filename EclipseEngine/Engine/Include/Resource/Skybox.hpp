#pragma once
#include "RHIInterfaces/ICubeMap.hpp"
#include "Resource/IResource.hpp"
#include "Resource/TextureExtention.hpp"
#include "Resource/Mesh.hpp"
#include "Resource/ShaderProgram.hpp"
#include <vector>
#include <string>

namespace Resource
{
	class Skybox : public IResource
	{
	public:
		ECLIPSE_ENGINE Skybox(std::string _name = "");
		ECLIPSE_ENGINE ~Skybox() override;

		ECLIPSE_ENGINE void GetFileContent(std::string _path) override;
		ECLIPSE_ENGINE void Generate(RHI::IRenderInterface* _rdrInterface) override;
		ECLIPSE_ENGINE void SetModelName(std::string _model);
		ECLIPSE_ENGINE void SetShaderName(std::string _shader);

		ECLIPSE_ENGINE void Draw();

		ECLIPSE_ENGINE void Delete() override;

	private:
		RHI::IRenderInterface* m_rdrInter = nullptr;

		RHI::ICubeMap* m_cubeMap = nullptr;
		Resource::Mesh* m_mesh = nullptr;
		Resource::ShaderProgram* m_shaderProgram = nullptr;
		std::string m_meshName = "";
		std::string m_shaderProgramName = "";

		TEXTURE_EXTENSION textureExtention = TEXTURE_EXTENSION::JPG;
		std::vector<unsigned char*> m_data;
		int m_width = 0;
		int m_height = 0;

		const char* m_faces[6] = {	"/right",
									"/left",
									"/top",
									"/bottom",
									"/front",
									"/back" };
	};
}