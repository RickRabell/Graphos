#pragma once
#include "../Prerequisites.h"
#include "Component.h"

class 
Texture : public Component {
public:
	Texture() = default;

	Texture(const std::string& textureName, const std::string& extension = "png")
		: m_textureName(textureName), m_eextension(extension), Component(TEXTURE) {
		if (!m_texture.loadFromFile(m_textureName + "." + m_eextension)) {
			std::cout << "Error loading texture: " << m_textureName << "." << m_eextension << std::endl;
		}
	}
	
	virtual
	~Texture() = default;

	void
	start() override {};

	void
	update(float deltaTime) override;

	void
	render(const EngineUtilities::TSharedPointer<Window>& window) override;

	void
	destroy() override{};

	sf::Texture&
	getTexture() {
		return m_texture;
	}

private:
	sf::Texture m_texture;
	std::string m_textureName;
	std::string m_eextension;
};