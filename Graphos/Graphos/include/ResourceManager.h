#pragma once
#include "Prerequisites.h"
#include "ECS/Texture.h"

/**
 * @class ResourceManager
 * @brief Singleton class responsible for managing and loading textures.
 *
 * The ResourceManager class provides functionality to load, store, and retrieve textures.
 * It ensures that textures are loaded only once and shared across the application.
 * Copying and assignment are disabled to enforce singleton behavior.
 */
class
ResourceManager {
private:
	/**
  * @brief Default constructor for ResourceManager.
  * Private to enforce singleton pattern.
  */
	ResourceManager() = default;

	/**
  * @brief Destructor for ResourceManager.
  * Private to enforce singleton pattern.
  */
	~ResourceManager() = default;

public:
	/**
  * @brief Deleted copy constructor to prevent copying.
  */
	ResourceManager(const ResourceManager&) = delete;

	/**
  * @brief Deleted assignment operator to prevent copying.
  */
	ResourceManager& operator=(const ResourceManager&) = delete;

	/**
  * @brief Gets the singleton instance of ResourceManager.
  * @return Reference to the singleton ResourceManager instance.
  */
	static ResourceManager& 
	getInstance() {
		static ResourceManager instance;
		return instance;
	}

	/**
  * @brief Loads a texture from a file with the specified extension.
  * @param fileName The name of the texture file to load.
  * @param extension The file extension (e.g., "png", "jpg").
  * @return True if the texture was loaded successfully, false otherwise.
  */
	bool
	loadTexture(const std::string& fileName, const std::string& extension);

	/**
  * @brief Retrieves a shared pointer to a loaded texture by file name.
  * @param fileName The name of the texture file.
  * @return Shared pointer to the Texture if found, nullptr otherwise.
  */
	EngineUtilities::TSharedPointer<Texture>
	getTexture(const std::string& fileName);

private:
	/**
  * @brief Map storing loaded textures, keyed by file name.
  */
	std::unordered_map<std::string, EngineUtilities::TSharedPointer<Texture>> m_textures;
};