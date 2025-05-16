#pragma once
#include "IGraphicsResource.hpp"
#include "RHIInterfaces/IVertexArray.hpp"
#include "RHIInterfaces/IVertexBuffer.hpp"
#include "RHIInterfaces/IIndexBuffer.hpp"
#include "RHIInterfaces/Vertex.hpp"
#include "Core/Particles/ParticleRenderData.hpp"
#include <vector>

namespace Resource
{
	class Mesh : public IGraphicsResource
	{
	public:
		ECLIPSE_ENGINE Mesh(std::string _name = "");
		ECLIPSE_ENGINE ~Mesh() override;

		ECLIPSE_ENGINE void GetFileContent(std::string _path) override;
		ECLIPSE_ENGINE std::vector<Math::Vec3> GetVerticesPosition() const;
		ECLIPSE_ENGINE std::vector<unsigned int> GetVerticesIndex() const;
		ECLIPSE_ENGINE void Generate(RHI::IRenderInterface* _rdrInterface) override;

		ECLIPSE_ENGINE void Draw() const;
		ECLIPSE_ENGINE void BindVertexArray();
		ECLIPSE_ENGINE void UnbindVertexArray();

		ECLIPSE_ENGINE void Delete() override;

	private:
		RHI::IRenderInterface* m_rdrInter = nullptr;

		std::vector<RHI::Vertex> m_vertexBuffer;
		std::vector<unsigned int> m_indexBuffer;

		RHI::IVertexArray* m_vertexArrayObject = nullptr;
		RHI::IVertexBuffer* m_vertexBufferObject = nullptr;
		RHI::IIndexBuffer* m_indexBufferObject = nullptr;
	};
}