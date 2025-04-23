#pragma once
#include "Maths.hpp"
#include <vector>

namespace Resource
{
	struct ModelData;
}

namespace RHI
{
	struct DirLightData;
	struct PointLightData;
	struct SpotLightData;

	class IGraphicPipeline
	{
	public:
		IGraphicPipeline() = default;
		virtual ~IGraphicPipeline() = default;

		virtual void Init(int _width, int _height) = 0;
		virtual void Rescale(int _width, int _height) = 0;
		virtual void Delete() = 0;

		virtual void Draw(Math::Mat4 _VP, Math::Vec3 _viewPos, std::vector<Resource::ModelData> _staticModels, std::vector<RHI::DirLightData> _dirLights, std::vector<RHI::PointLightData> _pointLights, std::vector<RHI::SpotLightData> _spotLights) = 0;
		virtual unsigned int GetFinalTexture() const = 0;

	protected:
		int m_width = 0;
		int m_height = 0;
	};
}