#pragma once
#include "Actor.h"
#include "../Prerequisites.h"

class A_Racer : public Actor {
public:
	//A_Racer(std::string name, int initialPos);
	~A_Racer() = default;

	A_Racer(const std::string& name, int initialPos);

	void
	update(float deltaTime) override;

	void
	setSpeed(float speed);

	void
	setWayPoints(const std::vector<sf::Vector2f>& waypoints);

	void
	resetPos();

private:
	//int m_place;
	//float m_speed = 200.0f;
	//float m_maxSpeed = 250.0f;
	float m_steeringForce = 10.0f;
	//std::vector<sf::Vector2f> m_waypoints;
	//int m_initialPosIndex = 0;
	//int m_currentWaypointIndex = 0;

	// --- Variables para ajustar jugabilidad ---
	float m_minApproachSpeed = 50.0f;
	float m_maxApproachSpeed = 100.0f;
	float m_minWaypointSpeed = 100.0f;
	float m_maxWaypointSpeed = 200.0f;
	float m_arrivalThreshold = 10.0f;

	void
	seekToWaypoint(float deltaTime);

	float
	calculateCurvature(const sf::Vector2f& prev, const sf::Vector2f& curr, const sf::Vector2f& next);
};