#pragma once
#include "IResource.hpp"
#include "RHIInterfaces/IVertexArray.hpp"
#include "RHIInterfaces/IVertexBuffer.hpp"
#include "RHIInterfaces/IIndexBuffer.hpp"
#include "RHIInterfaces/Vertex.hpp"
#include <vector>

namespace Resource
{
	class Mesh : public IResource
	{
	public:
		ECLIPSE_ENGINE Mesh(std::string _name = "");
		ECLIPSE_ENGINE ~Mesh() override;

		ECLIPSE_ENGINE void GetFileContent(std::string _path) override;
		ECLIPSE_ENGINE void Generate(RHI::IRenderInterface* _rdrInterface) override;

		ECLIPSE_ENGINE void Draw() const;

		ECLIPSE_ENGINE void Delete() override;

	private:
		RHI::IRenderInterface* m_rdrInter = nullptr;

		std::vector<RHI::Vertex> m_vertexBuffer;
		std::vector<uint32_t> m_indexBuffer;

		RHI::IVertexArray* m_vertexArrayObject = nullptr;
		RHI::IVertexBuffer* m_vertexBufferObject = nullptr;
		RHI::IIndexBuffer* m_indexBufferObject = nullptr;
	};
}