#include "ECS/A_Player.h"
#include "ECS/Actor.h"
#include "ECS/Transform.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <limits>
#include <algorithm>

// Utilidad: distancia entre dos puntos
static float 
Distance(const sf::Vector2f& a, const sf::Vector2f& b) {
  float dx = a.x - b.x;
  float dy = a.y - b.y;
  return std::sqrt(dx * dx + dy * dy);
}

// Utilidad: tiempo total en segundos desde el inicio (para desempate)
static float 
GetTotalTimeSeconds() {
  static sf::Clock s_globalClock;
  return s_globalClock.getElapsedTime().asSeconds();
}

A_Player::A_Player(const std::string& name, int initialPos)
    : Actor(name) {
    m_initialPosIndex = initialPos;
    m_currentWaypointIndex = initialPos;
    m_laps = 0;
    m_totalLaps = 3;
    m_hasStartedLap = false;
    m_place = 0;
    m_totalTime = 0.f;
    m_lastWaypointPassed = initialPos;
    m_frozen = false;
}

void 
A_Player::update(float deltaTime) {
  if (!m_frozen)
    HandleInput(deltaTime);

  // Lógica de waypoints y vueltas
  if (!m_waypoints.empty()) {
    sf::Vector2f pos = getComponent<Transform>()->getPosition();
    int nextIdx = (m_lastWaypointPassed + 1) % m_waypoints.size();
    float distToNext = Distance(pos, m_waypoints[nextIdx]);
    const float threshold = 32.f; // Ajusta según tamaño del checkpoint

    // Solo avanza si está cerca del siguiente waypoint en orden
    if (distToNext < threshold) {
      m_lastWaypointPassed = nextIdx;
      m_currentWaypointIndex = nextIdx;

      // Si pasa del último al primero (sin contar el spawn inicial)
      if (nextIdx == 0 && m_hasStartedLap) {
        ++m_laps;
        if (m_laps >= m_totalLaps) {
          m_frozen = true;
          moveSpeed = 0.f;
          m_totalTime = GetTotalTimeSeconds();
        }
        m_hasStartedLap = false;
      }
      // Marca que ya salió del primer waypoint
      if (nextIdx != 0) m_hasStartedLap = true;
    }
  }
}

void 
A_Player::HandleInput(float deltaTime) {
  sf::Vector2f movement(0.f, 0.f);
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) movement.y -= 1.f;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) movement.y += 1.f;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) movement.x -= 1.f;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) movement.x += 1.f;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) movement.y -= 1.f;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) movement.y += 1.f;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) movement.x -= 1.f;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) movement.x += 1.f;

  if (movement.x != 0.f || movement.y != 0.f) {
    float length = std::sqrt(movement.x * movement.x + movement.y * movement.y);
    if (length != 0.f) movement /= length;
    getComponent<Transform>()->setPosition(getComponent<Transform>()->getPosition() 
                                           + movement * moveSpeed * deltaTime);
  }
}

// --- Métodos utilitarios para el podio ---
float 
A_Player::getTotalTime() const { return m_totalTime; }

int 
A_Player::getLastWaypointPassed() const { return m_lastWaypointPassed; }

float 
A_Player::getDistToNextWaypoint() const {
  if (m_waypoints.empty()) return 0.f;

  int nextIdx = (m_lastWaypointPassed + 1) % m_waypoints.size();
  auto transform = getComponent<Transform>();

  if (!transform) return 0.f;

  return Distance(transform->getPosition(), m_waypoints[nextIdx]);
}

bool 
A_Player::isFrozen() const { return m_frozen; }

void 
A_Player::freeze() { m_frozen = true; moveSpeed = 0.f; }