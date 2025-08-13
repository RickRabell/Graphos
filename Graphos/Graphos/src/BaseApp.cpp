#include "BaseApp.h"
#include "ResourceManager.h"
#include "EngineGUI.h"
#include "ECS/A_Racer.h"
#include "ECS/A_Player.h"
#include <algorithm>

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

  // --- Crear un Racer IA como ejemplo ---
  auto IA_01 = EngineUtilities::MakeShared<A_Racer>("IA 01", 0);
  if (IA_01) {
    IA_01->setWayPoints(m_waypoints);
    IA_01->getComponent<CShape>()->createShape(CIRCLE);
    IA_01->getComponent<CShape>()->setFillColor(sf::Color::Blue);
    IA_01->getComponent<Transform>()->setPosition(m_waypoints[0]);
    IA_01->getComponent<Transform>()->setScale(sf::Vector2f(3.0f, 3.0f));
    IA_01->setSpeed(200.f);

    if (!resourceMan.loadTexture("Sprites/Mushroom", "png")) {
      MESSAGE("BaseApp", "init", "Can't load the Texture");
    }
    IA_01->setTexture(resourceMan.getTexture("Sprites/Mushroom"));

    m_actors.push_back(IA_01);
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

  // --- Crear el jugador controlable ---
  m_player = EngineUtilities::MakeShared<A_Player>("Player", 0);
  if (m_player) {
      m_player->m_waypoints = m_waypoints; 
      m_player->getComponent<CShape>()->createShape(CIRCLE);
      m_player->getComponent<CShape>()->setFillColor(sf::Color::Red); 
      m_player->getComponent<Transform>()->setPosition(m_waypoints[0]); // Asegura posición visible
      m_player->getComponent<Transform>()->setScale(sf::Vector2f(3.0f, 3.0f));
      m_player->setTotalLaps(3);

      if (!resourceMan.loadTexture("Sprites/Mushroom", "png")) {
          MESSAGE("BaseApp", "init", "Can't load the Player Texture");
      } else {
          m_player->setTexture(resourceMan.getTexture("Sprites/Mushroom"));
      }

      m_actors.push_back(m_player);
  } else {
      ERROR("BaseApp", "init", "Failed to create Player pointer");
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

  updatePodium();
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

  renderTimer();
  
  // Usar un actor válido para la ventana de Laps
  if (!m_player.isNull()) {
      renderLapsWindow(m_player);
  } else if (!m_actors.empty() && !m_actors[0].isNull()) {
      renderLapsWindow(m_actors[0]);
  }
  
  renderPodiumWindow();

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

    int totalSeconds = static_cast<int>(std::max(0.f, elapsed.asSeconds()));
    int totalMilliseconds = static_cast<int>(elapsed.asMilliseconds());

    int minutes = 0;
    int seconds = 0;
    int milliseconds = 0;

    // Solo realiza la división/módulo si el divisor es distinto de cero
    if (totalSeconds >= 60) {
        minutes = totalSeconds / 60;
        seconds = totalSeconds % 60;
    } else {
        minutes = 0;
        seconds = totalSeconds;
    }

    if (totalMilliseconds >= 1000) {
        milliseconds = totalMilliseconds % 1000;
    } else if (totalMilliseconds > 0) {
        milliseconds = totalMilliseconds;
    } else {
        milliseconds = 0;
    }

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

void BaseApp::updatePodium() {
    /* Filtrar actores nulos antes de ordenar
    std::vector<EngineUtilities::TSharedPointer<Actor>> validActors;
    for (const auto& actor : m_actors) {
        if (!actor.isNull()) {
            validActors.push_back(actor);
        }
    }
    
    // Ordenar por criterios (vueltas, waypoint actual, distancia)
    std::sort(validActors.begin(), validActors.end(), [this](const auto& a, const auto& b) {
        // Criterio 1: Número de vueltas (más vueltas = mejor posición)
        if (a->getLaps() != b->getLaps())
            return a->getLaps() > b->getLaps();
            
        // Criterio 2: Índice de waypoint actual (waypoint más avanzado = mejor posición)
        if (a->m_currentWaypointIndex != b->m_currentWaypointIndex)
            return a->m_currentWaypointIndex > b->m_currentWaypointIndex;
            
        // Criterio 3: Distancia al siguiente waypoint (más cerca = mejor posición)
        if (!m_waypoints.empty() && a->m_waypoints.size() > 0 && b->m_waypoints.size() > 0) {
            auto aPos = a->getComponent<Transform>()->getPosition();
            auto bPos = b->getComponent<Transform>()->getPosition();
            
            // Calcular índice del siguiente waypoint de forma segura
            int aNextIdx = (a->m_currentWaypointIndex + 1) % a->m_waypoints.size();
            int bNextIdx = (b->m_currentWaypointIndex + 1) % b->m_waypoints.size();
            
            auto aNext = a->m_waypoints[aNextIdx];
            auto bNext = b->m_waypoints[bNextIdx];
            
            float aDist = std::sqrt((aPos.x - aNext.x)*(aPos.x - aNext.x) + 
                                    (aPos.y - aNext.y)*(aPos.y - aNext.y));
            float bDist = std::sqrt((bPos.x - bNext.x)*(bPos.x - bNext.x) + 
                                    (bPos.y - bNext.y)*(bPos.y - bNext.y));
                                    
            return aDist < bDist;
        }
        
        // En caso de no poder comparar, mantener el orden actual
        return false;
    });
    
    // Asignar lugares usando los actores válidos ordenados
    for (size_t i = 0; i < validActors.size(); ++i) {
        validActors[i]->setPlace(static_cast<int>(i) + 1);
    }*/
    // Filtrar actores nulos antes de ordenar
  std::vector<EngineUtilities::TSharedPointer<Actor>> validActors;
  for (const auto& actor : m_actors) {
    if (!actor.isNull()) validActors.push_back(actor);
  }

  // Congelar todos si algún actor terminó
  bool raceFinished = false;
  for (const auto& actor : validActors) {
    if (actor->getLaps() >= actor->getTotalLaps()) {
      raceFinished = true;
      break;
    }
  }
  if (raceFinished) {
    for (const auto& actor : validActors) {
      // Si es A_Player
      auto player = dynamic_cast<A_Player*>(actor.get());
      if (player && !player->isFrozen()) player->freeze();
      // Si es IA, congelar velocidad
      auto racer = dynamic_cast<A_Racer*>(actor.get());
      if (racer) racer->setSpeed(0.f);
    }
  }

  // Ordenar por (laps desc, currentWaypoint desc, distToNext asc, totalTime asc)
  std::sort(validActors.begin(), validActors.end(), [](const auto& a, const auto& b) {
    if (a->getLaps() != b->getLaps())
      return a->getLaps() > b->getLaps();
    if (a->m_currentWaypointIndex != b->m_currentWaypointIndex)
      return a->m_currentWaypointIndex > b->m_currentWaypointIndex;

    float aDist = 0.f, bDist = 0.f;
    // Métodos utilitarios para obtener distancia al siguiente waypoint
    auto aPlayer = dynamic_cast<const A_Player*>(a.get());
    auto bPlayer = dynamic_cast<const A_Player*>(b.get());
    if (aPlayer) aDist = aPlayer->getDistToNextWaypoint();
    else {
      if (!a->m_waypoints.empty()) {
        aDist = Distance(a->getComponent<Transform>()->getPosition(),
          a->m_waypoints[(a->m_currentWaypointIndex + 1) % a->m_waypoints.size()]);
      }
      else {
        aDist = std::numeric_limits<float>::max(); // Assign a large value to indicate no valid waypoint
      }
    }
    if (bPlayer) bDist = bPlayer->getDistToNextWaypoint();
    else {
      if (!b->m_waypoints.empty()) {
        bDist = Distance(b->getComponent<Transform>()->getPosition(),
          b->m_waypoints[(b->m_currentWaypointIndex + 1) % b->m_waypoints.size()]);
      }
      else {
        bDist = std::numeric_limits<float>::max(); // Assign a large value to indicate no valid waypoint
      }
    }
    if (aDist != bDist)
      return aDist < bDist;

    // Desempate por tiempo total (si existe)
    float aTime = 0.f, bTime = 0.f;
    if (aPlayer) aTime = aPlayer->getTotalTime();
    if (bPlayer) bTime = bPlayer->getTotalTime();
    return aTime < bTime;
    });

  // Asignar lugares usando los actores válidos ordenados
  for (size_t i = 0; i < validActors.size(); ++i) {
    validActors[i]->setPlace(static_cast<int>(i) + 1);
  }
}

void BaseApp::renderLapsWindow(const EngineUtilities::TSharedPointer<Actor>& actor) {
    if (!actor) return; // <-- Evita acceso nulo
    ImGui::Begin("LAPS");
    ImGui::SetWindowSize(ImVec2(700, 100), ImGuiCond_FirstUseEver);

    int currentLap = actor->getLaps();
    int totalLaps = actor->getTotalLaps();
    ImGui::Text("%d / %d", currentLap, totalLaps);

    ImGui::End();
}

void BaseApp::renderPodiumWindow() {
    ImGui::Begin("PODIUM");
    ImGui::SetWindowSize(ImVec2(300, 400), ImGuiCond_FirstUseEver);

    for (const auto& actor : m_actors) {
        if (!actor) continue; // <-- Evita actores nulos
        ImGui::Text("%d° : %s", actor->getPlace(), actor->getName().c_str());
        // Si tienes el sprite, puedes mostrarlo con ImGui::Image
        // Ejemplo:
        // if (auto shape = actor->getComponent<CShape>()) {
        //     auto& texture = shape->getTexture();
        //     ImGui::Image(texture, ImVec2(32, 32));
        // }
    }

    ImGui::End();
}

