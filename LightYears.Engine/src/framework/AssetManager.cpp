#include "framework/AssetManager.h"

namespace LightYear
{
	Unique<AssetManager> AssetManager::m_assetManager{ nullptr };

	AssetManager::AssetManager() :
		m_rootDirectory{ }
	{

	}

	AssetManager& AssetManager::Get()
	{
		if (m_assetManager)
			return *m_assetManager;

		m_assetManager = Unique<AssetManager>{ new AssetManager };

		return *m_assetManager;
	}

	Shared<sf::Texture> AssetManager::LoadTexture(const std::string& path)
	{
		auto foundTexture = m_loadedTextureMap.find(path);
		if (foundTexture != m_loadedTextureMap.end())
			return foundTexture->second;

		Shared<sf::Texture> newTexture{ new sf::Texture };
		if (!newTexture->loadFromFile(m_rootDirectory + path))
		{
			LOG("Could not find texture path: %s", path.c_str());
			return Shared<sf::Texture> { nullptr };
		}

		m_loadedTextureMap.insert({ path, newTexture });

		return newTexture;
	}

	void AssetManager::CleanCycle()
	{
		for (auto texture = m_loadedTextureMap.begin(); texture != m_loadedTextureMap.end();)
		{
			if (!texture->second.unique())
			{
				texture++;
				continue;
			}

			LOG("Cleaning texture: %s", texture->first.c_str());
			texture = m_loadedTextureMap.erase(texture);
		}
	}

	void AssetManager::SetRootDirectory(const std::string& directory)
	{
		m_rootDirectory = directory;
	}
}