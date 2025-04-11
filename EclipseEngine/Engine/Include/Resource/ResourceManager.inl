#pragma once
#include "Resource/ShaderProgram.hpp"
#include "Resource/Skybox.hpp"
#include <type_traits>
#include <typeinfo>
#include <iostream>

namespace Resource
{
	template <typename T>
	T* ResourceManager::AddResourceToLoad(std::string _resourceName, std::string _resourcePath)
	{
		T* resource = new T;
		m_resourcesToLoad[_resourceName] = resource;
		m_resourcesPath[_resourceName] = _resourcePath;
		return resource;
	}

	template <typename T>
	T* ResourceManager::AddResourceToLoad(std::string _resourceName, std::string _resourcePath1, std::string _resourcePath2)
	{
		const std::type_info& typeT = typeid(T);
		const std::type_info& typeShaderProgram = typeid(ShaderProgram);
		if (typeT == typeShaderProgram)
		{
			ShaderProgram* shaderResource = new ShaderProgram;
			shaderResource->SetVertFragShader(_resourcePath1, _resourcePath2);
			m_resourcesToGenerate[_resourceName] = shaderResource;
			return shaderResource;
		}

		T* resource = new T;
		m_resourcesToLoad[_resourceName] = resource;
		m_resourcesPath[_resourceName] = _resourcePath1;
		return resource;
	}

	template <typename T>
	T* ResourceManager::AddResourceToLoad(std::string _resourceName, std::string _resourcePath1, std::string _resourcePath2, std::string _resourcePath3)
	{
		const std::type_info& typeT = typeid(T);
		const std::type_info& typeSkybox = typeid(Skybox);
		if (typeT == typeSkybox)
		{
			Skybox* skyboxResource = new Skybox;
			skyboxResource->SetModelName(_resourcePath2);
			skyboxResource->SetShaderName(_resourcePath3);
			m_resourcesToLoad[_resourceName] = skyboxResource;
			m_resourcesPath[_resourceName] = _resourcePath1;
			return skyboxResource;
		}

		T* resource = new T;
		m_resourcesToLoad[_resourceName] = resource;
		m_resourcesPath[_resourceName] = _resourcePath1;
		return resource;
	}

	template <typename T>
	T* ResourceManager::GetResource(std::string _resourceName)
	{
		auto it = m_resourcesReady.find(_resourceName);
		if (it == m_resourcesReady.end())
			return nullptr;
		else
			return static_cast<T*>(it->second);
	}

	template <typename T>
	std::vector<std::string> ResourceManager::GetAllResourceWithType()
	{
		std::vector<std::string> resourcesName;
		const std::type_info& typeT = typeid(T);
		for (std::map<std::string, IResource*>::iterator it = m_resourcesReady.begin(); it != m_resourcesReady.end(); ++it)
		{
			const std::type_info& typeIt = typeid(*it->second);
			if (typeT == typeIt)
				resourcesName.push_back(it->first);
		}
		return resourcesName;
	}
}