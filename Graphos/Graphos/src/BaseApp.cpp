#include "BaseApp.h"
#include "ResourceManager.h"

BaseApp::~BaseApp() {
}

int 
BaseApp::run() {
  if (!init()) {
    ERROR("BaseApp", 
          "run", 
          "Initializes result on a false statement, check method validations");
  }
  while (m_windowPtr->isOpen()) {
    m_windowPtr->handleEvents(m_engineGUI);
    update();
    render();
  }
  destroy();
	return 0;
}

bool 
BaseApp::init() {
	ResourceManager& resourceMan = ResourceManager::getInstance();

  m_windowPtr = EngineUtilities::MakeShared<Window>(1920, 1080, "Graphos");
  if (!m_windowPtr) {
    ERROR("BaseApp", 
           "init", 
           "Failed to create window pointer, check memory allocation");
    return false;
  }

  // Initialize the Engine GUI
  m_engineGUI.init(m_windowPtr);
  //m_window = new Window(1920, 1080, "Graphos");
  //m_circle = new sf::CircleShape(100.0f);
  //m_circle->setFillColor(sf::Color::Green);
  //m_circle->setPosition(200.f, 150.f);
  /*m_shapePtr = EngineUtilities::MakeShared<CShape>();
  if (m_shapePtr) {
    m_shapePtr->createShape(ShapeType::CIRCLE);
    m_shapePtr->setFillColor(sf::Color::Green);
    m_shapePtr->setPosition(200.f, 150.f);
  }*/

  // Create Circle Actor
  m_ACircle = EngineUtilities::MakeShared<Actor>("Circle Actor");
  if (m_ACircle) {
    m_ACircle->getComponent<CShape>()->createShape(CIRCLE);
    m_ACircle->getComponent<CShape>()->setFillColor(sf::Color::White);
    m_ACircle->getComponent<Transform>()->setPosition(sf::Vector2(75.f, 85.f));
    m_ACircle->getComponent<Transform>()->setScale(sf::Vector2(3.f, 3.f));

    if (!resourceMan.loadTexture("Sprites/Mushroom", "png")) {
      MESSAGE("BaseApp", 
              "init", 
				      "Can't load the Texture");
    }
		m_ACircle->setTexture(resourceMan.getTexture("Sprites/Mushroom"));

		m_actors.push_back(m_ACircle);
    //m_ACircle->setTexture()
    //m_ACircle->setName("CircleActor");
  } 

  // Create Track
  m_track = EngineUtilities::MakeShared<Actor>("Track Actor");
  if (m_track) {
    
    m_track->getComponent<CShape>()->createShape(RECTANGLE);
    m_track->getComponent<CShape>()->setFillColor(sf::Color::Cyan);
    m_track->getComponent<Transform>()->setPosition(sf::Vector2(0.f, 0.f));
    m_track->getComponent<Transform>()->setScale(sf::Vector2(23.f, 21.5f));

    if (!resourceMan.loadTexture("Sprites/Rainbow_Track", "png")) {
      MESSAGE("BaseApp",
              "init",
              "Can't load the Texture");
    }
    m_track->setTexture(resourceMan.getTexture("Sprites/Rainbow_Track"));
    
		m_actors.push_back(m_track);
  }
  /*
  m_checks = EngineUtilities::MakeShared<Actor>("Track Actor");
  if (m_checks) {
    
    m_checks->getComponent<CShape>()->createShape(CIRCLE);
    m_checks->getComponent<CShape>()->setFillColor(sf::Color::Red);
    m_checks->getComponent<Transform>()->setPosition(sf::Vector2(400.f, 900.f));
    m_checks->getComponent<Transform>()->setScale(sf::Vector2(0.5f, 0.5f));
  }*/
  else {
    ERROR("BaseApp", 
          "init", 
          "Failed to create Actor pointer, check memory allocation");
    return false;
  }

  return true;
}

void 
BaseApp::update() {
  if (!m_windowPtr.isNull()) {
    m_windowPtr->update();
  }

	// Actualizar el GUI del Engine
	m_engineGUI.update(m_windowPtr, m_windowPtr->deltaTime);
	m_engineGUI.outliner(m_actors);
	m_engineGUI.inspector(m_actors);
	ImGui::ShowDemoWindow();
  

  // Seek
  // Obtener el componente de Transformación del Actor
  if (!m_ACircle.isNull() && !m_waypoints.empty()) {
    m_ACircle->update(m_windowPtr->deltaTime.asSeconds());

    if (!m_track.isNull()) {
      m_track->update(m_windowPtr->deltaTime.asSeconds());
    }

    /*if (!m_checks.isNull()) {
      m_checks->update(m_windowPtr->deltaTime.asSeconds());
    }*/
    
		// Waypoint actual
		sf::Vector2f targetPos = m_waypoints[m_currentWaypointIndex];

    // Posición actual del destino (punto recorrido)
    //sf::Vector2f targetPos(1200.f, 150.f);

		// Llamar al seek del transform
		m_ACircle->getComponent<Transform>()->seek(targetPos, 
                                               200.f, 
                                               m_windowPtr->deltaTime.asSeconds(), 
                                               10.0f);

		// Si llegó al waypoint, avanza al siguiente
		sf::Vector2f pos = m_ACircle->getComponent<Transform>()->getPosition();
    float dist = std::sqrt((pos.x - targetPos.x) * (pos.x - targetPos.x) +
			(pos.y - targetPos.y) * (pos.y - targetPos.y));

    if (dist <= 10.0f) {
      m_currentWaypointIndex = (m_currentWaypointIndex + 1) % m_waypoints.size();
		}
  }
}

void 
BaseApp::render() {
  // Limpiar, dibujar y mostrar
  //m_windowPtr->clear();
  //m_windowPtr->draw(*m_circle);
  //m_windowPtr->display();

  if (!m_windowPtr) {
    return;
  }
  m_windowPtr->clear();
  /*if (m_shapePtr) {
    m_shapePtr->render(m_windowPtr);
  }*/
  /*if (!m_ACircle.isNull()) {
    m_ACircle->getComponent<CShape>()->render(m_windowPtr);
  }*/
  if (!m_track.isNull()) {
    m_track->getComponent<CShape>()->render(m_windowPtr);
  }

  /*if (!m_checks.isNull()) {
    m_checks->getComponent<CShape>()->render(m_windowPtr);
  }*/
  
  if (!m_ACircle.isNull()) {
    //m_ACircle->render(m_windowPtr);
    m_ACircle->getComponent<CShape>()->render(m_windowPtr);
	}

  m_windowPtr->render();

	m_engineGUI.render(m_windowPtr);

  m_windowPtr->display();
}

void 
BaseApp::destroy() {
  // Destroy ImGui
	m_engineGUI.destroy();
  //delete m_circle;
  //m_window->destroy();
}
