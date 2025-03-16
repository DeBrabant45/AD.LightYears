#pragma once

#include "framework/Core.h"
#include "framework/ICleanCycle.h"
#include <SFML/Graphics.hpp>

namespace LightYear
{
	class AssetManager : public ICleanCycle
	{
	public:
		~AssetManager() = default;
		static AssetManager& Get();
		Shared<sf::Texture> LoadTexture(const std::string& path);
		void CleanCycle();
		void SetRootDirectory(const std::string& directory);

	protected:
		AssetManager();

	private:
		static Unique<AssetManager> m_assetManager;
		Dictionary<std::string, Shared<sf::Texture>> m_loadedTextureMap;
		std::string m_rootDirectory;
	};
}