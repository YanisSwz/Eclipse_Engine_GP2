#include "Resource/ResourceManager.hpp"

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

	void ResourceManager::LoadAllResources()
	{
		for (std::map<std::string, IResource*>::iterator it = m_resourcesToLoad.begin(); it != m_resourcesToLoad.end(); ++it)
		{
			it->second->GetFileContent(m_resourcesPath[it->first]);
			AddResourceToGenerate(it->second, it->first);
		}
		m_resourcesToLoad.clear();
	}

	void ResourceManager::GenerateAllResources(RHI::IRenderInterface* _rendererInterface)
	{
		while (!m_resourcesToGenerate.empty())
		{
			std::vector<std::string> resourcesGenerated;
			for (std::map<std::string, IResource*>::iterator it = m_resourcesToGenerate.begin(); it != m_resourcesToGenerate.end(); ++it)
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

	void ResourceManager::AddResourceToGenerate(IResource* _resource, std::string _resourceName)
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