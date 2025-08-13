#include "ECS/A_Player.h"
#include "ECS/Transform.h"
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <limits>

A_Player::A_Player(const std::string& name, int initialPos)
  : Actor(name) {}

void A_Player::update(float deltaTime) {
    HandleInput(deltaTime);
}

void A_Player::HandleInput(float deltaTime) {
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
        if (length != 0.f) {
            movement /= length; // Normalize
        }
        getComponent<Transform>()->setPosition(getComponent<Transform>()->getPosition() + movement * moveSpeed * deltaTime);
    }

    // Calcula el waypoint más cercano
    if (!m_waypoints.empty()) {
        sf::Vector2f pos = getComponent<Transform>()->getPosition();
        float minDist = std::numeric_limits<float>::max();
        int closestIdx = 0;
        for (size_t i = 0; i < m_waypoints.size(); ++i) {
            float d = std::hypot(pos.x - m_waypoints[i].x, pos.y - m_waypoints[i].y);
            if (d < minDist) {
                minDist = d;
                closestIdx = static_cast<int>(i);
            }
        }
        // Si pasa del último al primero, cuenta la vuelta
        if (closestIdx == 0 && m_currentWaypointIndex == m_waypoints.size() - 1) {
            if (m_hasStartedLap) {
                m_laps++;
                m_hasStartedLap = false;
                if (m_laps >= m_totalLaps) {
                    moveSpeed = 0.f;
                }
            }
        } else if (closestIdx != 0) {
            m_hasStartedLap = true;
        }
        m_currentWaypointIndex = closestIdx;
    }
}