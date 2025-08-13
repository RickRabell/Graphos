#pragma once
#include "Actor.h"
#include "../Prerequisites.h"

/**
 * @class A_Racer
 * @brief Represents a racer actor in the ECS system, capable of following waypoints and simulating racing behavior.
 *
 * The A_Racer class extends the Actor class, providing additional functionality for movement, speed control,
 * waypoint navigation, and gameplay tuning. It is designed for use in racing games or simulations where
 * entities must follow a path and exhibit dynamic movement characteristics.
 */
class 
A_Racer : public Actor {
public:
	//A_Racer(std::string name, int initialPos);
	/**
  * @brief Default destructor for A_Racer.
  */
	~A_Racer() = default;

	/**
  * @brief Constructs a new A_Racer with a given name and initial position index.
  * @param name The name of the racer.
  * @param initialPos The initial position index for the racer.
  */
	A_Racer(const std::string& name, int initialPos);

	/**
  * @brief Updates the racer's state each frame.
  * @param deltaTime The time elapsed since the last update.
  */
	void
	update(float deltaTime) override;

	/**
  * @brief Sets the current speed of the racer.
  * @param speed The new speed value to set.
  */
	void
	setSpeed(float speed);

	/**
  * @brief Sets the list of waypoints for the racer to follow.
  * @param waypoints A vector of 2D positions representing the path.
  */
	void
	setWayPoints(const std::vector<sf::Vector2f>& waypoints);

	/**
  * @brief Resets the racer's position to its initial state.
  */
	void
	resetPos();

private:
	/**
  * @brief The steering force applied to the racer's movement.
  */
	float m_steeringForce = 10.0f;

	// --- Variables para ajustar jugabilidad ---
	/**
  * @brief The minimum speed when approaching a waypoint.
  */
	float m_minApproachSpeed = 50.0f;
	/**
  * @brief The maximum speed when approaching a waypoint.
  */
	float m_maxApproachSpeed = 100.0f;
	/**
  * @brief The minimum speed when moving between waypoints.
  */
	float m_minWaypointSpeed = 100.0f;
	/**
  * @brief The maximum speed when moving between waypoints.
  */
	float m_maxWaypointSpeed = 200.0f;
	/**
  * @brief The distance threshold to consider a waypoint as reached.
  */
	float m_arrivalThreshold = 10.0f;

	/**
  * @brief Moves the racer towards the current waypoint.
  * @param deltaTime The time elapsed since the last update.
  */
	void
	seekToWaypoint(float deltaTime);

	/**
  * @brief Calculates the curvature between three waypoints.
  * @param prev The previous waypoint position.
  * @param curr The current waypoint position.
  * @param next The next waypoint position.
  * @return The calculated curvature value.
  */
	float
	calculateCurvature(const sf::Vector2f& prev, 
                     const sf::Vector2f& curr, 
                     const sf::Vector2f& next);
};