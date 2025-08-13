#pragma once
#include "../Prerequisites.h"
#include "Entity.h"
#include "CShape.h"
#include "Transform.h"

/*
	* @class Actor
	* @brief Represents an actor entity in the ECS (Entity Component System) architecture.
	*
	* The Actor class is a specialized type of Entity that serves as a container for components
	* such as shapes, transforms, and other behaviors. Actors are the primary objects in the scene,
	* capable of being updated, rendered, and managed within the engine. Each Actor has a unique name
	* and can hold multiple components, allowing for flexible composition of functionality.
	*
	* Usage:
	*   - Create an Actor and attach components to define its behavior and appearance.
	*   - Override update and render methods to customize per-frame logic and drawing.
	*   - Use getComponent<T>() to retrieve specific components attached to the Actor.
	*
	* Inherits from:
	*   Entity - Provides base functionality for all entities in the ECS system.
*/
class 
Actor : Entity {
public:
	/*
		*  @brief Default constructor for Actor.
	*/
	Actor() = default;
	
	/*
		*  @brief Constructs an Actor with a specified name.
		*  @param actorName Name of the actor.
	*/
	Actor(const std::string& actorName);
	
	/*
		*  @brief Virtual destructor for Actor.
	*/
	virtual 
	~Actor() = default;
	
	/*
		*  @brief Called when the actor is started or initialized.
	*/
	void
	start() override;

	/*
		*  @brief Updates the actor with the given delta time.
		*  @param deltaTime Time elapsed since last update.
	*/
	void
	update(float deltaTime) override;

	/*
		*  @brief Renders the actor using the provided window.
		*  @param window Shared pointer to the rendering window.
	*/
	void
	render(const EngineUtilities::TSharedPointer<Window>& window) override;

	/*
		*  @brief Called when the actor is destroyed.
	*/
	void
	destroy() override;

	/*
		*  @brief Sets the texture for the actor.
		*  @param texture Shared pointer to the texture to be applied.
	*/
	void
	setTexture(const EngineUtilities::TSharedPointer<Texture>& texture);

	/*
		*  @brief Gets the name of the actor.
		*  @return The actor's name as a string.
	*/
	std::string
	getName() {
		return m_name;
	}

  /*
		*  @brief Retrieves a component of type T attached to the actor.
		*  @tparam T Type of the component to retrieve.
		*  @return Shared pointer to the component if found, otherwise an empty pointer.
  */
	template<typename T>
	EngineUtilities::TSharedPointer<T>
	getComponent();

	/*
		*  @brief Const version of getComponent that retrieves a component of type T.
		*  @tparam T Type of the component to retrieve.
		*  @return Const shared pointer to the component if found, otherwise an empty pointer.
	*/
	template<typename T>
	EngineUtilities::TSharedPointer<T>
	getComponent() const;

  /*
  *  @brief Gets the current number of laps completed by the actor.
  */
  int 
  getLaps() const { return m_laps; }

  /*
  *  @brief Gets the total number of laps required for the actor.
  */
  int 
  getTotalLaps() const { return m_totalLaps; }

  /*
  *  @brief Sets the total number of laps for the actor.
  *  @param laps The total number of laps to set.
  */
  void
  setTotalLaps(int laps) { m_totalLaps = laps; }

  /*
  *  @brief Gets the current place or position of the actor.
  */
  int 
  getPlace() const { return m_place; }

  /*
  *  @brief Sets the current place or position of the actor.
  *  @param place The place to set for the actor.
  */
  void
  setPlace(int place) { m_place = place; }

  public:
  /*
  *  @brief List of waypoints for the actor to follow.
  */
  std::vector<sf::Vector2f> m_waypoints;
  /*
  *  @brief The current speed of the actor.
  */
  float m_speed = 200.0f;
  /*
  *  @brief The maximum speed the actor can reach.
  */
  float m_maxSpeed = 250.0f;
  /*
  *  @brief The initial index position of the actor.
  */
  int m_initialPosIndex = 0;
  /*
  *  @brief The current waypoint index the actor is targeting.
  */
  int m_currentWaypointIndex = 0;

  protected:
  /*
  *  @brief The number of laps completed by the actor.
  */
  int m_laps = 0;
  /*
  *  @brief The total number of laps required for the actor.
  */
  int m_totalLaps = 3;
  /*
  *  @brief Indicates if the actor has started a lap.
  */
  bool m_hasStartedLap = false;
  /*
  *  @brief The current place or position of the actor.
  */
  int m_place;

  private:
  /*
  *  @brief Name of the actor.
  */
  std::string m_name = "Actor";
};

/*
	*  @brief Retrieves a component of type T attached to the actor.
	*         Iterates through all components and returns the first matching type.
	*  @tparam T Type of the component to retrieve.
	*  @return Shared pointer to the component if found, otherwise an empty pointer.
*/
template<typename T>
inline EngineUtilities::TSharedPointer<T> 
Actor::getComponent() {
	for (auto& component : components) {
		EngineUtilities::TSharedPointer<T> 
		specificComponent =  component.template dynamic_pointer_cast<T>();

		if (specificComponent) {
		return specificComponent;
		}
	}
	// Devuelve un TSharedPointer vacío si no se encuentra el componente
	return EngineUtilities::TSharedPointer<T>();
}

/*
	*  @brief Retrieves a component of type T attached to the actor.
	*         Iterates through all components and returns the first matching type.
	*  @tparam T Type of the component to retrieve.
	*  @return Shared pointer to the component if found, otherwise an empty pointer.
*/
template<typename T>
inline EngineUtilities::TSharedPointer<T> 
Actor::getComponent() const {
    for (const auto& component : components) {
        EngineUtilities::TSharedPointer<T> 
        specificComponent = component.template dynamic_pointer_cast<T>();
        
        if (specificComponent) {
            return specificComponent;
        }
    }
    return EngineUtilities::TSharedPointer<T>();
}