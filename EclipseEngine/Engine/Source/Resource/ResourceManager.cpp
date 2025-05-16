#include "Resource/ResourceManager.hpp"
#include "Texture.hpp"
#include "ShaderProgram.hpp"
#include "GeoShader.hpp"
#include "Prefab.hpp"
#include <filesystem>

namespace Resource
{
	ResourceManager* ResourceManager::m_instance = nullptr;

	ResourceManager::ResourceManager()
	{
	}

	ResourceManager::~ResourceManager()
	{
	}

	ResourceManager& ResourceManager::GetInstance()
	{
		if (!m_instance)
			m_instance = new ResourceManager;
		return *m_instance;
	}

	void ResourceManager::DestroyInstance()
	{
		if (m_instance)
		{
			m_instance->Destroy();
			delete m_instance;
			m_instance = nullptr;
		}
	}

	void ResourceManager::LoadAllResourcesInAssetsFolder()
	{
		std::string resourceName;
		std::string resourcePath;
		for (const auto& entry : std::filesystem::directory_iterator("Assets/Models"))
		{
			resourceName = entry.path().filename().string();
			char popedChar;
			do
			{
				popedChar = resourceName[resourceName.size() - 1];
				resourceName.pop_back();
			} while (popedChar != '.');
			resourceName.append(".obj");
			resourcePath = entry.path().string();
			AddResourceToLoad<Resource::Mesh>(resourceName, resourcePath);
		}

		for (const auto& entry : std::filesystem::directory_iterator("Assets/Textures"))
		{
			resourceName = entry.path().filename().string();
			char popedChar;
			do
			{
				popedChar = resourceName[resourceName.size() - 1];
				resourceName.pop_back();
			} while (popedChar != '.');
			resourceName.append(".img");
			resourcePath = entry.path().string();
			AddResourceToLoad<Resource::Texture>(resourceName, resourcePath);
		}

		for (const auto& entry : std::filesystem::directory_iterator("Assets/Icons"))
		{
			resourceName = entry.path().filename().string();
			char popedChar;
			do
			{
				popedChar = resourceName[resourceName.size() - 1];
				resourceName.pop_back();
			} while (popedChar != '.');
			resourceName.append(".img");
			resourcePath = entry.path().string();
			AddResourceToLoad<Resource::Texture>(resourceName, resourcePath);
		}

		for (const auto& entry : std::filesystem::directory_iterator("Assets/Audio"))
		{
			resourceName = entry.path().filename().string();
			resourcePath = entry.path().string();
			AddResourceToLoad<Resource::AudioClip>(resourceName, resourcePath);
		}

		for (const auto& entry : std::filesystem::directory_iterator("Assets/Skybox"))
		{
			resourceName = entry.path().filename().string().append(".skb");
			resourcePath = entry.path().string().append("/");
			AddResourceToLoad<Resource::Skybox>(resourceName, resourcePath);
		}

		for (const auto& entry : std::filesystem::directory_iterator("Assets/Shaders/VertFragShaders/"))
		{
			// Load Vertex Shader
			if (entry.path().extension().string() == ".vert")
			{
				resourceName = entry.path().filename().string();
				resourcePath = entry.path().string();
				AddResourceToLoad<Resource::VertShader>(resourceName, resourcePath);
			}
			else if (entry.path().extension().string() == ".frag")
			{
				// Load Fragment Shader
				resourceName = entry.path().filename().string();
				resourcePath = entry.path().string();
				AddResourceToLoad<Resource::FragShader>(resourceName, resourcePath);

				resourcePath = entry.path().filename().string();
				// Load Shader Program
				char popedChar;
				do
				{
					popedChar = resourceName[resourceName.size() - 1];
					resourceName.pop_back();
					resourcePath.pop_back();
				} while (popedChar != '.');

				resourceName.append(".shd");
				resourcePath.append(".vert");

				AddResourceToLoad<Resource::ShaderProgram>(resourceName, resourcePath, entry.path().filename().string());
			}
		}

		if (std::filesystem::exists("Assets/Shaders/VertGeoFragShaders/"))
		{
			for (const auto& entry : std::filesystem::directory_iterator("Assets/Shaders/VertGeoFragShaders/"))
			{
				// Load Vertex Shader
				if (entry.path().extension().string() == ".vert")
				{
					resourceName = entry.path().filename().string();
					resourcePath = entry.path().string();
					AddResourceToLoad<Resource::VertShader>(resourceName, resourcePath);
				}
				// Load Fragment Shader
				else if (entry.path().extension().string() == ".frag")
				{
					resourceName = entry.path().filename().string();
					resourcePath = entry.path().string();
					AddResourceToLoad<Resource::FragShader>(resourceName, resourcePath);
				}
				else if (entry.path().extension().string() == ".geom")
				{
					// Load Geometry Shader
					resourceName = entry.path().filename().string();
					resourcePath = entry.path().string();
					AddResourceToLoad<Resource::GeoShader>(resourceName, resourcePath);

					resourcePath = entry.path().filename().string();
					// Load Shader Program
					char popedChar;
					do
					{
						popedChar = resourceName[resourceName.size() - 1];
						resourceName.pop_back();
						resourcePath.pop_back();
					} while (popedChar != '.');

					resourceName.append(".shd");
					std::string vertName = resourcePath + ".vert";
					std::string fragName = resourcePath + ".frag";
					std::string geoName = resourcePath + ".geom";

					AddResourceToLoad<Resource::ShaderProgram>(resourceName, vertName, fragName, geoName);
				}
			}

			for (const auto& entry : std::filesystem::directory_iterator("Assets/Prefabs"))
			{
				resourceName = entry.path().filename().string();
				resourcePath = entry.path().string();
				AddResourceToLoad<Resource::Prefab>(resourceName, resourcePath);
			}

			resourceName.clear();
			resourcePath.clear();
		}
	}

	void ResourceManager::LoadAllResources()
	{
		for (std::map<std::string, IResource*>::iterator it = m_resourcesToLoad.begin(); it != m_resourcesToLoad.end(); ++it)
		{
			it->second->GetFileContent(m_resourcesPath[it->first]);
			IGraphicsResource* res = dynamic_cast<IGraphicsResource*>(it->second);
			if (res != nullptr)
				AddResourceToGenerate(res, it->first);
			else
				AddResourceToReady(it->second, it->first);
		}
		m_resourcesToLoad.clear();
		m_resourcesPath.clear();
	}

	void ResourceManager::GenerateAllResources(RHI::IRenderInterface* _rendererInterface)
	{
		while (!m_resourcesToGenerate.empty())
		{
			std::vector<std::string> resourcesGenerated;
			for (std::map<std::string, IGraphicsResource*>::iterator it = m_resourcesToGenerate.begin(); it != m_resourcesToGenerate.end(); ++it)
			{
				it->second->Generate(_rendererInterface);
				AddResourceToReady(it->second, it->first);
				if (it->second->IsLoaded())
					resourcesGenerated.push_back(it->first);
			}
			for (std::string resourceName : resourcesGenerated)
				DeleteResourceToGenerate(resourceName);
		}
	}

	void ResourceManager::DestroyAllResources()
	{
		if (!m_resourcesReady.empty())
		{
			for (std::map<std::string, IResource*>::iterator it = m_resourcesReady.begin(); it != m_resourcesReady.end(); ++it)
				delete it->second;
			m_resourcesReady.clear();
		}
	}

	void ResourceManager::AddResourceToGenerate(IGraphicsResource* _resource, std::string _resourceName)
	{
		m_resourcesToGenerate[_resourceName] = _resource;
	}

	void ResourceManager::AddResourceToReady(IResource* _resource, std::string _resourceName)
	{
		m_resourcesReady[_resourceName] = _resource;
	}

	void ResourceManager::DeleteResourceToLoad(std::string _resourceName)
	{
		m_resourcesToLoad.erase(_resourceName);
	}

	void ResourceManager::DeleteResourceToGenerate(std::string _resourceName)
	{
		m_resourcesToGenerate.erase(_resourceName);
	}

	void ResourceManager::DeleteResourceToReady(std::string _resourceName)
	{
		m_resourcesReady.erase(_resourceName);
	}

	void ResourceManager::Destroy()
	{
		DestroyAllResources();
	}
}