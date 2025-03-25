#pragma once
#include "RHIInterfaces/ICubeMap.hpp"
#include "Resource/IResource.hpp"
#include "Resource/TextureExtention.hpp"
#include "Resource/Model.hpp"
#include "Resource/ShaderProgram.hpp"
#include <vector>


namespace Resource
{
	class Skybox : public IResource
	{
	public:
		ECLIPSE_ENGINE Skybox();
		ECLIPSE_ENGINE ~Skybox() override;

		ECLIPSE_ENGINE void GetFileContent(const char* _skyboxFolderPath, TEXTURE_EXTENSION _textureExtention);
		ECLIPSE_ENGINE void Generate(RHI::IRenderInterface* _rdrInterface) override;
		ECLIPSE_ENGINE void SetModel(Resource::Model* _model);
		ECLIPSE_ENGINE void SetShader(Resource::ShaderProgram* _shader);

		ECLIPSE_ENGINE void Draw() const;

		ECLIPSE_ENGINE void Delete();

	private:
		RHI::IRenderInterface* m_rdrInter = nullptr;

		RHI::ICubeMap* m_cubeMap = nullptr;
		Resource::Model* m_model = nullptr;
		Resource::ShaderProgram* m_shaderProgram = nullptr;

		TEXTURE_EXTENSION textureExtention;
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