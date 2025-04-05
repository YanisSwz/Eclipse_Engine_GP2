#include "Resource/Model.hpp"
#define TINYOBJLOADER_IMPLEMENTATION
#include "tiny_obj_loader.h"
#include <filesystem>
#include <iostream>

namespace Resource
{
	Model::Model()
	{
	}

	Model::~Model()
	{
		Delete();
	}

	void Model::GetFileContent(std::string _path)
	{
		// Verify if Texture file path exists
		if (!std::filesystem::exists(_path))
		{
			std::cout << "The file: " << _path << " not found!" << std::endl;
			return;
		}

		// TODO Load the model
		tinyobj::attrib_t attributes;
		std::vector<tinyobj::shape_t> shapes;
		std::vector<tinyobj::material_t> materials;
		std::string warnings;
		std::string errors;

		if (!tinyobj::LoadObj(&attributes, &shapes, &materials, &warnings, &errors, _path.c_str()))
		{
			std::cout << "The object with the path: " << _path << " not found!" << std::endl;
			return;
		}

		for (int i = 0; i < shapes.size(); i++)
		{
			tinyobj::shape_t& shape = shapes[i];
			tinyobj::mesh_t& mesh = shape.mesh;
			for (int j = 0; j < mesh.indices.size(); j++)
			{
				tinyobj::index_t index = mesh.indices[j];

				Math::Vec3 position{ attributes.vertices[index.vertex_index * 3],
									 attributes.vertices[index.vertex_index * 3 + 1],
									 attributes.vertices[index.vertex_index * 3 + 2] };
				Math::Vec3 normal{ attributes.normals[index.normal_index * 3],
								   attributes.normals[index.normal_index * 3 + 1],
								   attributes.normals[index.normal_index * 3 + 2] };
				Math::Vec2 texCoord{ attributes.texcoords[index.texcoord_index * 2],
									 attributes.texcoords[index.texcoord_index * 2 + 1], };
				RHI::Vertex vert;
				vert.pos = position;
				vert.textUV = texCoord;
				vert.normal = normal;
				m_indexBuffer.push_back(static_cast<uint32_t>(m_vertexBuffer.size()));
				m_vertexBuffer.push_back(vert);
			}
		}
	}

	void Model::Generate(RHI::IRenderInterface* _rdrInterface)
	{
		m_rdrInter = _rdrInterface;

		m_vertexArrayObject = _rdrInterface->InstantiateVertexArray();
		m_vertexBufferObject = _rdrInterface->InstantiateVertexBuffer();
		m_indexBufferObject = _rdrInterface->InstantiateIndexBuffer();

		m_vertexArrayObject->Init();
		m_vertexArrayObject->Bind();
		m_vertexBufferObject->Init(&m_vertexBuffer[0], m_vertexBuffer.size() * sizeof(RHI::Vertex));
		m_indexBufferObject->Init(&m_indexBuffer[0], m_indexBuffer.size() * sizeof(uint32_t));

		// Vertex position,		/		Normal,		 /	    Texture position
		m_vertexArrayObject->LinkVertexBuffer(*m_vertexBufferObject, 0, 3, RHI::IFLAGS::TYPE_FLOAT, sizeof(RHI::Vertex), (void*)offsetof(RHI::Vertex, pos));
		m_vertexArrayObject->LinkVertexBuffer(*m_vertexBufferObject, 1, 3, RHI::IFLAGS::TYPE_FLOAT, sizeof(RHI::Vertex), (void*)offsetof(RHI::Vertex, normal));
		m_vertexArrayObject->LinkVertexBuffer(*m_vertexBufferObject, 2, 2, RHI::IFLAGS::TYPE_FLOAT, sizeof(RHI::Vertex), (void*)offsetof(RHI::Vertex, textUV));

		m_vertexArrayObject->Unbind();
		m_vertexBufferObject->Unbind();
		m_indexBufferObject->Unbind();

		m_vertexBuffer.clear();
		m_indexBuffer.clear();

		bIsLoaded = true;
	}

	void Model::Draw() const
	{
		m_indexBufferObject->Draw(m_vertexArrayObject);
	}

	void Model::Delete()
	{
		if (!m_vertexBuffer.empty())
			m_vertexBuffer.clear();
		if (!m_indexBuffer.empty())
			m_indexBuffer.clear();
		m_vertexArrayObject->Delete();
		m_vertexBufferObject->Delete();
		m_indexBufferObject->Delete();
		m_rdrInter->DestroyVertexArray(m_vertexArrayObject);
		m_rdrInter->DestroyVertexBuffer(m_vertexBufferObject);
		m_rdrInter->DestroyIndexBuffer(m_indexBufferObject);
	}
}