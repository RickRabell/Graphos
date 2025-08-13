#include "window.h"
#include "EngineGUI.h"

Window::Window(int width, int height, const std::string& title) {
	// Crear ventana con SFML 3
	m_windowPtr = EngineUtilities::MakeUnique<sf::RenderWindow>(
		sf::VideoMode({ static_cast<unsigned int>(width),
										static_cast<unsigned int>(height) }),
		title,
		sf::Style::Default
	);

	if (!m_windowPtr.isNull()) {
		m_windowPtr->setFramerateLimit(60);
		MESSAGE("Window", "Window", "Window created successfully");
	}
	else {
		ERROR("Window", "Window", "Failed to create window");
	}
}

Window::~Window() {
	m_windowPtr.release();
}

void
Window::handleEvents(EngineGUI& engineGUI) {
		// Process events
	while (const std::optional event = m_windowPtr->pollEvent())
	{
		engineGUI.processEvent(*m_windowPtr, *event);
		// Close window: exit
		if (event->is<sf::Event::Closed>())
			m_windowPtr->close();
	}
}


bool
Window::isOpen() const {
	// Check that window is not null
	if (!m_windowPtr.isNull()) {
		return m_windowPtr->isOpen();
	}
	else {
		ERROR("Window", "isOpen", "Window is null");
		return false;
	}
}

void
Window::clear(const sf::Color& color) {
	if (!m_windowPtr.isNull()) {
		m_windowPtr->clear(color);
	}
	else {
		ERROR("Window", "clear", "Window is null");
	}
}

void
Window::draw(const sf::Drawable& drawable, const sf::RenderStates& states) {
	if (!m_windowPtr.isNull()) {
		m_windowPtr->draw(drawable, states);
	}
	else {
		ERROR("Window", "draw", "Window is null");
	}
}

void
Window::display() {
	if (!m_windowPtr.isNull()) {
		m_windowPtr->display();
	}
	else {
		ERROR("Window", "display", "Window is null");
	}
}

void
Window::update() {
	// Almacena el deltaTime una sola vez
	deltaTime = clock.restart();
}

void
Window::render() {
}

void
Window::destroy() {
	m_windowPtr.release();
}


/*#include <window.h>

Window::Window(int width, int height, const std::string& title) {
  //Inicializar la ventana
  //m_window = new sf::RenderWindow(sf::VideoMode(width, height), title);
  m_windowPtr = EngineUtilities::MakeUnique<sf::RenderWindow>(sf::VideoMode(width, height), title);

  if (!m_windowPtr.isNull()) {
    m_windowPtr->setFramerateLimit(60); //Limitar a 60 fps
    MESSAGE("windos", "window", "window created successfully");
  }
  else {
    ERROR("window", "window", "Failed to create window");
  }

  // Initialize the ImGui Resource
	ImGui::SFML::Init(*m_windowPtr);
}

Window::~Window() {
	ImGui::SFML::Shutdown();
  m_windowPtr.release();
  //SAFE_PTR_RELEASE(m_window);
}

void
Window::handleEvents() {
  sf::Event event;
  while (m_windowPtr->pollEvent(event)) {
		ImGui::SFML::ProcessEvent(event); // Procesar eventos de ImGui
    // Cerrar la ventana si el usuario lo indica
    if (event.type == sf::Event::Closed) {
      m_windowPtr->close();
    }
  }
}

bool
Window::isOpen() const {
  // Check that window is not null
  if (!m_windowPtr.isNull()) {
    return m_windowPtr->isOpen();
  }
  else {
    ERROR("Window", "isOpen", "Window is null")
    return false;
  }
}

void
Window::clear(const sf::Color& color) {
  if (!m_windowPtr.isNull()) {
    m_windowPtr->clear(color);
  }
  else {
    ERROR("Window", "clear", "Window is null")
  }
}

void
Window::draw(const sf::Drawable& drawable, const sf::RenderStates& states) {
  if (!m_windowPtr.isNull()) {
    m_windowPtr->draw(drawable, states);
  }
  else {
    ERROR("Window", "draw", "Window is null")
  }
}

void
Window::display() {
  if (!m_windowPtr.isNull()) {
    m_windowPtr->display();
  }
  else {
    ERROR("Window", "display", "Window is null")
  }
}

void
Window::update() {
  // Almacena el deltaTime una sola vez
  deltaTime = clock.restart();

	ImGui::SFML::Update(*m_windowPtr, deltaTime); // Actualizar ImGui con el deltaTime
}

void
Window::render() {
	ImGui::SFML::Render(*m_windowPtr); // Renderizar ImGui
}

void 
Window::destroy() {
	ImGui::SFML::Shutdown(); // Shutdown ImGui
  //SAFE_PTR_RELEASE(m_window);
  m_windowPtr.release();
}*/