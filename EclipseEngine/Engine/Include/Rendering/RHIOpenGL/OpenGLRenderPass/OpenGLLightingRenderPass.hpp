#pragma once
#include "RHIOpenGL/OpenGLRenderPass/OpenGLRenderPass.hpp"
#include "Resource/ShaderProgram.hpp"
#include "Maths.hpp"
#include "RHIInterfaces/Lights.hpp"
#include <vector>
#include <glad/glad.h>

namespace RHI::OpenGL
{
	class OpenGLFrameBuffer;

	class OpenGLLightingRenderPass : public OpenGLRenderPass
	{
	public:
		OpenGLLightingRenderPass();
		~OpenGLLightingRenderPass() override;

		void Init(int _width, int _height) override;
		void Rescale(int _width, int _height) override;
		void Delete() override;

		void Draw(Math::Vec3 _viewPos, GLuint _gPosition, GLuint _gNormal, GLuint _gAlbedoSpec, Math::Vec4 _ambientLight, std::vector<RHI::DirLightData> _dirLightsData, std::vector<RHI::PointLightData> _pointLightsData, std::vector<RHI::SpotLightData> _spotLightsData);

	private:
		const char* m_LightingShaderProgramName = "DeferredLighting.shd";
		Resource::ShaderProgram* m_shaderLight = nullptr;

		void SetDirLights(std::vector<RHI::DirLightData> _dirLightsData);
		void SetPointLights(std::vector<RHI::PointLightData> _pointLightsData);
		void SetSpotLights(std::vector<RHI::SpotLightData> _spotLightsData);
	};
}