#pragma once
#include "IResource.hpp"
#include "RHIInterfaces/IVertexArray.hpp"
#include "RHIInterfaces/IVertexBuffer.hpp"
#include "RHIInterfaces/IIndexBuffer.hpp"
#include "RHIInterfaces/Vertex.hpp"
#include <vector>
#include <string>

namespace Resource
{
	class Model : public IResource
	{
	public:
		ECLIPSE_ENGINE Model();
		ECLIPSE_ENGINE ~Model() override;

		ECLIPSE_ENGINE void GetFileContent(std::string _path);
		ECLIPSE_ENGINE void Generate(RHI::IRenderInterface* _rdrInterface) override;

		ECLIPSE_ENGINE void Draw() const;

		ECLIPSE_ENGINE void Delete();

	private:
		RHI::IRenderInterface* m_rdrInter = nullptr;

		std::vector<RHI::Vertex> m_vertexBuffer;
		std::vector<uint32_t> m_indexBuffer;

		RHI::IVertexArray* m_vertexArrayObject = nullptr;
		RHI::IVertexBuffer* m_vertexBufferObject = nullptr;
		RHI::IIndexBuffer* m_indexBufferObject = nullptr;
	};
}