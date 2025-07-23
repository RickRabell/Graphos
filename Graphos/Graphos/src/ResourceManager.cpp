#include "ResourceManager.h"

bool
ResourceManager::loadTexture(const std::string& fileName,
	const std::string& extension) {
	// Verfy if the texture is already loaded
	if (m_textures.find(fileName) != m_textures.end()) {
		return true; // Texture already loaded
	}

	// Create and load the texture
	auto texture = EngineUtilities::MakeShared<Texture>(fileName, extension);
	m_textures[fileName] = texture;
	return true;
}

EngineUtilities::TSharedPointer<Texture>
ResourceManager::getTexture(const std::string & fileName) {
	// Search for the texture in the map
	auto it = m_textures.find(fileName);
	if (it != m_textures.end()) {
		return it->second; // Return the found texture
	}

	// Warning Message
	std::cerr << "[Resource Manager] Texture not found: " << fileName << ". Using default texture \n";

	const std::string defaultKey = "Default";

	// Verify if default texture is loaded
	auto defaultIt = m_textures.find(defaultKey);
	if (defaultIt != m_textures.end()) {
		return defaultIt->second; // Return the default texture
	}

	// Load the deafult texture
	auto defaultTexture = EngineUtilities::MakeShared<Texture>(defaultKey, "png");
	m_textures[defaultKey] = defaultTexture;
	return defaultTexture; // Return the newly loaded default texture
}