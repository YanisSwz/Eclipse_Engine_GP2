#include "RHIOpenGL/OpenGLRenderPass/OpenGLParticleRenderPass.hpp"
#include "Resource/ResourceManager.hpp"
#include "Resource/ShaderProgram.hpp"

namespace RHI::OpenGL
{
	OpenGLParticleRenderPass::OpenGLParticleRenderPass()
	{
	}

	OpenGLParticleRenderPass::~OpenGLParticleRenderPass()
	{
		Delete();
	}

	void OpenGLParticleRenderPass::Init(int _width, int _height)
	{
		m_width = _width;
		m_height = _height;
		m_particleShader = Resource::ResourceManager::GetInstance().GetResource<Resource::ShaderProgram>(m_particleShaderProgramName);

		// Create the UBO
		glGenBuffers(1, &m_ubo);
		glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
		glBufferData(GL_UNIFORM_BUFFER, MAX_PARTICLE_SIZE * sizeof(Core::ParticleRenderData), nullptr, GL_DYNAMIC_DRAW);
		glBindBuffer(GL_UNIFORM_BUFFER, 0);
	}

	void OpenGLParticleRenderPass::Rescale(int _width, int _height)
	{
		m_width = _width;
		m_height = _height;
	}

	void OpenGLParticleRenderPass::Delete()
	{
	}

	void OpenGLParticleRenderPass::Draw(Math::Mat4 _VP, std::vector<std::vector<Core::ParticleRenderData>> _particlesData)
	{
		m_particleShader->Bind();
		m_particleShader->SetMat4("VP", _VP, true);
		m_particleShader->SetFloat("windowWidth", static_cast<float>(m_width));
		m_particleShader->SetFloat("windowHeight", static_cast<float>(m_height));

		for (int i = 0; i < _particlesData.size(); ++i)
		{
			if (_particlesData[i].empty())
				continue;

			glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
			GLvoid* p = glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY);
			memcpy(p, _particlesData[i].data(), _particlesData[i].size() * sizeof(Core::ParticleRenderData));
			glUnmapBuffer(GL_UNIFORM_BUFFER);

			unsigned int block_index = glGetUniformBlockIndex(m_particleShader->GetProgramID(), "shader_data");
			GLuint binding_point_index = 0;
			glBindBufferBase(GL_UNIFORM_BUFFER, binding_point_index, m_ubo);
			glUniformBlockBinding(m_particleShader->GetProgramID(), block_index, binding_point_index);

			glDrawArraysInstanced(GL_POINTS, 0, 1, static_cast<GLsizei>(_particlesData[i].size()));
		}

		m_particleShader->Unbind();
	}
}