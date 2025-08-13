#include "BaseApp.h"
#include "ResourceManager.h"
#include "EngineGUI.h"
#include "ECS/A_Racer.h"

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
  // Reset the application timer when the app starts
  m_appTimer.restart();

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

	// Define waypoints for the path
  
  //m_waypoints.push_back(sf::Vector2f(400.f, 900.f));
  m_waypoints.push_back(sf::Vector2f(75.f, 85.f));
	//m_waypoints.push_back(sf::Vector2f(175.f, 85.f));

	//m_waypoints.push_back(sf::Vector2f(1200.f, 85.f));
  m_waypoints.push_back(sf::Vector2f(1300.f, 85.f));
  //m_waypoints.push_back(sf::Vector2f(1300.f, 185.f));

	//m_waypoints.push_back(sf::Vector2f(1300.f, 362.f));
  m_waypoints.push_back(sf::Vector2f(1300.f, 462.f));
  //m_waypoints.push_back(sf::Vector2f(1200.f, 462.f));


  m_waypoints.push_back(sf::Vector2f(540.f, 462.f));
  m_waypoints.push_back(sf::Vector2f(540.f, 683.f));
  m_waypoints.push_back(sf::Vector2f(1675.f, 683.f));
  m_waypoints.push_back(sf::Vector2f(1675.f, 947.f));
  m_waypoints.push_back(sf::Vector2f(820.f, 947.f));
  m_waypoints.push_back(sf::Vector2f(790.f, 905.f));
  m_waypoints.push_back(sf::Vector2f(400.f, 905.f));
  m_waypoints.push_back(sf::Vector2f(380.f, 947.f));
  m_waypoints.push_back(sf::Vector2f(75.f, 947.f));
  

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

    //m_actors.push_back(m_track);
  }

  // -----------------------------------------------------------------------------------------------
  // Path Markers
  for (const auto& waypoint : m_waypoints) {
    auto marker = EngineUtilities::MakeShared<CShape>();
    marker->createShape(ShapeType::CIRCLE);
    marker->setFillColor(sf::Color::Yellow);
    marker->setPosition(waypoint);
    marker->setScale(sf::Vector2f(1.f, 1.f));

    m_path.push_back(marker);
	}

  // ------------------------------------------------------------------------------------------------

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
  } 
  /*
  m_checks = EngineUtilities::MakeShared<Actor>("Track Actor");
  if (m_checks) {
    
    m_checks->getComponent<CShape>()->createShape(CIRCLE);
    m_checks->getComponent<CShape>()->setFillColor(sf::Color::Red);
    m_checks->getComponent<Transform>()->setPosition(sf::Vector2(400.f, 900.f));
    m_checks->getComponent<Transform>()->setScale(sf::Vector2(0.5f, 0.5f));
  }*/

	auto racer1 = EngineUtilities::MakeShared<A_Racer>("Racer 1", 0);
  if (racer1) {
		racer1->setWayPoints(m_waypoints);
    racer1->getComponent<CShape>()->createShape(CIRCLE);
    racer1->getComponent<CShape>()->setFillColor(sf::Color::Green);
    racer1->getComponent<Transform>()->setPosition(sf::Vector2(75.f, 85.f));
    racer1->getComponent<Transform>()->setScale(sf::Vector2(3.0f, 3.0f));
		racer1->setSpeed(200.f);

    if (!resourceMan.loadTexture("Sprites/Mushroom", "png")) {
      MESSAGE("BaseApp",
        "init",
        "Can't load the Texture");
    }
    racer1->setTexture(resourceMan.getTexture("Sprites/Mushroom"));

    m_actors.push_back(racer1);
  }
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
  
  renderTimer();

	ImGui::ShowDemoWindow();
  
  if(!m_track.isNull()) {
    m_track->update(m_windowPtr->deltaTime.asSeconds());
	}

  for (auto& actor : m_actors) {
    if (!actor.isNull()) {
      actor->update(m_windowPtr->deltaTime.asSeconds());
    }
	}

  if(!m_waypoints.empty()) {
		sf::Vector2f targetPos = m_waypoints[m_currentWaypointIndex];
		sf::Vector2f pos = m_ACircle->getComponent<Transform>()->getPosition();

		float dx = targetPos.x - pos.x;
		float dy = targetPos.y - pos.y;
		float distance = std::sqrt(dx * dx + dy * dy);

    if (distance < 10.0f) { // Si no ha llegado al waypoint
      m_currentWaypointIndex++;
      if (m_currentWaypointIndex >= static_cast<int>(m_waypoints.size())) {
        m_currentWaypointIndex = 0; // Reiniciar al primer waypoint
			}
    }

    m_ACircle->getComponent<Transform>()->seek(targetPos, 
                                               200.f, 
                                               m_windowPtr->deltaTime.asSeconds(), 
			                                         10.0f, 75.0f);
	}

  // Seek
  // Obtener el componente de Transformación del Actor
  /*if (!m_ACircle.isNull() && !m_waypoints.empty()) {
    m_ACircle->update(m_windowPtr->deltaTime.asSeconds());

    if (!m_track.isNull()) {
      m_track->update(m_windowPtr->deltaTime.asSeconds());
    }

    /*if (!m_checks.isNull()) {
      m_checks->update(m_windowPtr->deltaTime.asSeconds());
    }//
    
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
  }*/
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

  /*if (!m_ACircle.isNull()) {
    //m_ACircle->render(m_windowPtr);
    m_ACircle->getComponent<CShape>()->render(m_windowPtr);
  }*/

  for (auto& markers : m_path) {
		markers->render(m_windowPtr);
	}

  for (auto& actor : m_actors) {
    if (!actor.isNull()) {
      actor->render(m_windowPtr);
      //actor->getComponent<CShape>()->render(m_windowPtr);
    }
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

void
BaseApp::renderTimer() {
    // Get the elapsed time
    sf::Time elapsed = m_appTimer.getElapsedTime();
    
    // Calculate minutes, seconds, and milliseconds
    int minutes = static_cast<int>(elapsed.asSeconds()) / 60;
    int seconds = static_cast<int>(elapsed.asSeconds()) % 60;
    int milliseconds = static_cast<int>(elapsed.asMilliseconds()) % 1000;
    
    // Create a formatted string for the timer
    char timeStr[32];
    std::sprintf(timeStr, "%02d:%02d:%03d", minutes, seconds, milliseconds);
    
    // Display the timer with ImGui
    ImGui::Begin("TIME");
    ImGui::SetWindowSize(ImVec2(700, 300), ImGuiCond_FirstUseEver);
    
    // Make the text larger and centered
    ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]); // Use default font
    float windowWidth = ImGui::GetWindowSize().x;
    float textWidth = ImGui::CalcTextSize(timeStr).x;
    ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
    
    ImGui::Text("%s", timeStr);
    ImGui::PopFont();
    
    ImGui::End();
}
/*
void
BaseApp::renderTimer() {
  // Get the elapsed time
  sf::Time elapsed = m_appTimer.getElapsedTime();

  // Calculate minutes, seconds, and milliseconds
  int minutes = static_cast<int>(elapsed.asSeconds()) / 60;
  int seconds = static_cast<int>(elapsed.asSeconds()) % 60;
  int milliseconds = static_cast<int>(elapsed.asMilliseconds()) % 1000;

  // Create a formatted string for the timer
  char timeStr[32];
  std::sprintf(timeStr, "%02d:%02d:%03d", minutes, seconds, milliseconds);

  /* Set window flags for positioning
  ImGuiWindowFlags windowFlags = ImGuiWindowFlags_NoMove |
    ImGuiWindowFlags_NoResize |
    ImGuiWindowFlags_NoCollapse |
    ImGuiWindowFlags_AlwaysAutoResize;*

  // Calculate position for upper right corner (with 10px padding)
  ImVec2 windowSize(200, 100);
  ImVec2 windowPos(ImGui::GetIO().DisplaySize.x - windowSize.x - 10, 10);

  // Set the window position before creating it
  ImGui::SetNextWindowPos(windowPos, ImGuiCond_Always);
  ImGui::SetNextWindowSize(windowSize, ImGuiCond_FirstUseEver);

  // Display the timer with ImGui
  ImGui::Begin("TIME");

  // Make the text larger and centered
  ImGui::PushFont(ImGui::GetIO().Fonts->Fonts[0]); // Use default font
  float windowWidth = ImGui::GetWindowSize().x;
  float textWidth = ImGui::CalcTextSize(timeStr).x;
  ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);

  ImGui::Text("%s", timeStr);
  ImGui::PopFont();

  ImGui::End();
}*/

