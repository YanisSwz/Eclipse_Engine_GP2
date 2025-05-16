#pragma once
#include "RHIOpenGL/OpenGLRenderPass/OpenGLRenderPass.hpp"
#include "Maths.hpp"
#include "Core/Particles/ParticleRenderData.hpp"
#include <vector>
#include <glad/glad.h>

namespace Resource
{
	class ShaderProgram;
}

namespace RHI::OpenGL
{
	class OpenGLFrameBuffer;
	class ShaderProgram;

	class OpenGLParticleRenderPass : public OpenGLRenderPass
	{
	public:
		OpenGLParticleRenderPass();
		~OpenGLParticleRenderPass() override;

		void Init(int _width, int _height) override;
		void Rescale(int _width, int _height) override;
		void Delete() override;

		void Draw(Math::Mat4 _V, Math::Mat4 _P, std::vector<Core::ParticleEmitterRenderData> _particlesData);

	private:
		static const int MAX_PARTICLE_SIZE = 2000;

		const char* m_particleShaderProgramName = "ParticleShader.shd";
		Resource::ShaderProgram* m_particleShader = nullptr;

		GLuint m_ubo = 0;
	};
}