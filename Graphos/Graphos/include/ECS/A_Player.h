#pragma once

#include "ECS/Actor.h"

class A_Player : public Actor
{
public:
    A_Player(const std::string& name, int initialPos);

    void update(float deltaTime) override;

    // Utilidades para el podio y control global
    float getTotalTime() const;
    int getLastWaypointPassed() const;
    float getDistToNextWaypoint() const;
    bool isFrozen() const;
    void freeze();

private:
    float moveSpeed = 200.0f; // Units per second
    void HandleInput(float deltaTime);

    // Para lógica de vueltas y podio
    int m_lastWaypointPassed = 0;
    float m_totalTime = 0.f;
    bool m_frozen = false;
};
