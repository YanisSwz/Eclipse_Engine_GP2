#pragma once
#include "IResource.hpp"
#include "IGraphicsResource.hpp"
#include "ProjectExports.hpp"
#include <map>
#include <string>
#include <vector>

namespace Resource
{
	class ResourceManager
	{
	public:
		ECLIPSE_ENGINE ResourceManager();
		ECLIPSE_ENGINE ~ResourceManager();

		ECLIPSE_ENGINE static ResourceManager& GetInstance();
		ECLIPSE_ENGINE static void DestroyInstance();

		ECLIPSE_ENGINE void LoadAllResourcesInAssetsFolder();
		ECLIPSE_ENGINE void LoadAllResources();
		ECLIPSE_ENGINE void GenerateAllResources(RHI::IRenderInterface* _rendererInterface);
		ECLIPSE_ENGINE void DestroyAllResources();

		template <typename T>
		T* AddResourceToLoad(std::string _resourceName, std::string _resourcePath);

		template <typename T>
		T* AddResourceToLoad(std::string _resourceName, std::string _resourcePath1, std::string _resourcePath2);
		
		template <typename T>
		T* AddResourceToLoad(std::string _resourceName, std::string _resourcePath1, std::string _resourcePath2, std::string _resourcePath3);
		
		template <typename T>
		T* GetResource(std::string _resourceName);

		template <typename T>
		std::vector<std::string> GetAllResourceWithType();

	private:
		static ResourceManager* m_instance;
		
		std::map<std::string, std::string> m_resourcesPath;
		std::map<std::string, IResource*> m_resourcesToLoad;
		std::map<std::string, IGraphicsResource*> m_resourcesToGenerate;
		std::map<std::string, IResource*> m_resourcesReady;

		void AddResourceToGenerate(IGraphicsResource* _resource, std::string _resourceName);
		void AddResourceToReady(IResource* _resource, std::string _resourceName);

		void DeleteResourceToLoad(std::string _resourceName);
		void DeleteResourceToGenerate(std::string _resourceName);
		void DeleteResourceToReady(std::string _resourceName);

		void Destroy();
	};
}

#include "ResourceManager.inl"