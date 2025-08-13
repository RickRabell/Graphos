#pragma once

#include "ECS/Actor.h"

class A_Player : public Actor
{
public:
    A_Player(const std::string& name, int initialPos);

    void update(float deltaTime) override;

private:
    float moveSpeed = 200.0f; // Units per second

    void HandleInput(float deltaTime);
};
