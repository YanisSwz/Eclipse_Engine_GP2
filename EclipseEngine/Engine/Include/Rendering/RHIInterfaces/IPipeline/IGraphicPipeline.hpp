#pragma once
#include "Maths.hpp"
#include "RHIInterfaces/Lights.hpp"
#include "Particles/ParticleRenderData.hpp"
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
		
		virtual int PickObjectID(int _mousePosX, int _mousePosY) = 0;

		virtual void Draw(Math::Mat4 _VP, Math::Vec3 _viewPos, std::vector<Resource::ModelData> _staticModels, RHI::LightsData _lightsData, std::vector<std::vector<Core::ParticleRenderData>> _particleData) = 0;
		virtual unsigned int GetFinalTexture() const = 0;

	protected:
		int m_width = 0;
		int m_height = 0;
	};
}