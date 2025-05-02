#pragma once
#include "RHIInterfaces/IPipeline/IGraphicPipeline.hpp"

namespace RHI::OpenGL
{
	class OpenGLGraphicPipeline : public RHI::IGraphicPipeline
	{
	public:
		OpenGLGraphicPipeline() = default;
		virtual ~OpenGLGraphicPipeline() override = default;

		virtual void Init(int _width, int _height) override = 0;
		virtual void Rescale(int _width, int _height) override = 0;
		virtual void Delete() override = 0;
	
		virtual int PickObjectID(int _mousePosX, int _mousePosY) override = 0;

		virtual void Draw(Math::Mat4 _VP, Math::Vec3 _viewPos, std::vector<Resource::ModelData> _staticModels, Math::Vec4 _ambientLight, std::vector<RHI::DirLightData> _dirLights, std::vector<RHI::PointLightData> _pointLights, std::vector<RHI::SpotLightData> _spotLights) override = 0;
		virtual unsigned int GetFinalTexture() const override = 0;

	private:

	};
}