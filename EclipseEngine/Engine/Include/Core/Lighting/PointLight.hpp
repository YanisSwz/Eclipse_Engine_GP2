#pragma once
#include "ProjectExports.hpp"
#include "Lighting/ILight.hpp"
#include "RHIInterfaces/Lights.hpp"

namespace Core
{
	class PointLight : public ILight
	{
	public:
		static meta::factory<PointLight> factory;

		ECLIPSE_ENGINE PointLight() = default;
		ECLIPSE_ENGINE ~PointLight() = default;

		ECLIPSE_ENGINE RHI::PointLightData GetData() const;

		ECLIPSE_ENGINE inline float& GetDistanceRef() { return m_distance; }

		ECLIPSE_ENGINE inline float GetDistance() const { return m_distance; }
		ECLIPSE_ENGINE inline float GetConstAtt() const { return m_constantAttenuation; }
		ECLIPSE_ENGINE inline float GetLinAtt() const { return m_linearAttenuation; }
		ECLIPSE_ENGINE inline float GetQuadAtt() const { return m_quadraticAttenuation; }

		ECLIPSE_ENGINE inline void SetDistance(float _distance) { m_distance = _distance; }
		ECLIPSE_ENGINE inline void SetConstAtt(float _constAtt) { m_constantAttenuation = _constAtt; }
		ECLIPSE_ENGINE inline void SetLinAtt(float _linAtt) { m_linearAttenuation = _linAtt; }
		ECLIPSE_ENGINE inline void SetQuadAtt(float _quadAtt) { m_quadraticAttenuation = _quadAtt; }

		ECLIPSE_ENGINE void Serialize(json& _j) override;
		ECLIPSE_ENGINE void Deserialize(const json& _j) override;

	private:
		float m_constantAttenuation = 1.f;
		float m_linearAttenuation = 0.09f;
		float m_quadraticAttenuation = 0.032f;
		float m_distance = 10.f;

		Math::Vec3 GetPosition() const;
	};
}