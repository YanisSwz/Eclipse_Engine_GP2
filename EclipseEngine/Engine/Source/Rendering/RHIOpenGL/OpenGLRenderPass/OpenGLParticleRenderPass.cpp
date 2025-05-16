#include "RHIOpenGL/OpenGLRenderPass/OpenGLParticleRenderPass.hpp"
#include "Resource/ResourceManager.hpp"
#include "Resource/ShaderProgram.hpp"
#include "Core/Particles/ParticleRenderData.hpp"
#include "Resource/Texture.hpp"

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

	void OpenGLParticleRenderPass::Draw(Math::Mat4 _V, Math::Mat4 _P, std::vector<Core::ParticleEmitterRenderData> _particlesData)
	{
		m_particleShader->Bind();
		m_particleShader->SetMat4("View", _V, true);
		m_particleShader->SetMat4("Proj", _P, true);

		for (int i = 0; i < _particlesData.size(); ++i)
		{
			if (_particlesData[i].particlesRenderData.empty() || !_particlesData[i].particleMesh)
				continue; 
			m_particleShader->SetInt("bIsBillboard", static_cast<int>(_particlesData[i].bIsBillboard));
			if (_particlesData[i].particleTexture)
			{
				_particlesData[i].particleTexture->Bind();
				m_particleShader->SetInt("bHasTexture", 1);
			}
			else
			{
				glBindTexture(GL_TEXTURE_2D, 0);
				m_particleShader->SetInt("bHasTexture", 0);
			}

			glBindBuffer(GL_UNIFORM_BUFFER, m_ubo);
			GLvoid* p = glMapBuffer(GL_UNIFORM_BUFFER, GL_WRITE_ONLY);
			memcpy(p, _particlesData[i].particlesRenderData.data(), _particlesData[i].particlesRenderData.size() * sizeof(Core::ParticleRenderData));
			glUnmapBuffer(GL_UNIFORM_BUFFER);

			unsigned int block_index = glGetUniformBlockIndex(m_particleShader->GetProgramID(), "particleDataBlock");
			GLuint binding_point_index = 0;
			glBindBufferBase(GL_UNIFORM_BUFFER, binding_point_index, m_ubo);
			glUniformBlockBinding(m_particleShader->GetProgramID(), block_index, binding_point_index);

			_particlesData[i].particleMesh->BindVertexArray();
			GLsizei count = static_cast<GLsizei>(_particlesData[i].particleMesh->GetVerticesIndex().size());
			GLsizei instanceCount = static_cast<GLsizei>(_particlesData[i].particlesRenderData.size());
			glDrawElementsInstanced(GL_TRIANGLES, count,
				GL_UNSIGNED_INT, 0, instanceCount);
			_particlesData[i].particleMesh->UnbindVertexArray();
		}

		m_particleShader->Unbind();
	}
}