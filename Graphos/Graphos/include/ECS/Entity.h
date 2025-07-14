#pragma once
#include "../Prerequisites.h"
#include "Component.h"

class 
Window;

/*
	* @class Entity
	* @brief Abstract base class for all entities in the ECS (Entity Component System).
	*
	* The Entity class serves as the foundational interface for all game or simulation objects
	* managed by the ECS system. Each entity can aggregate multiple components, which define
	* its behavior and data. Entities are responsible for managing their lifecycle, including
	* initialization, updating, rendering, and destruction.
	*
	* Key responsibilities:
	* - Manage a collection of components that define the entity's behavior.
	* - Provide lifecycle hooks: start, update, render, and destroy.
	* - Allow dynamic addition and retrieval of components.
	* - Maintain an active state and a unique identifier.
	*
	* Usage:
	* - Derive from Entity to implement specific game objects.
	* - Use addComponent<T>() to attach components.
	* - Use getComponent<T>() to retrieve components by type.
*/
class 
Entity {
public:

	/*
		*  @brief Virtual destructor for Entity.
	*/
	virtual
	~Entity() = default;

	/*
		*  @brief Called when the entity is started or initialized.
	*/
	virtual void
	start() = 0;

	/*
		*  @brief Updates the entity with the given delta time.
		*  @param deltaTime Time elapsed since last update.
	*/
	virtual void
	update(float deltaTime) = 0;

	/*
		*  @brief Renders the entity using the provided window.
		*  @param window Shared pointer to the rendering window.
	*/
	virtual void
	render(const EngineUtilities::TSharedPointer<Window>& window) = 0;
	
	/*
		*  @brief Called when the entity is destroyed.
	*/
	virtual void
	destroy() = 0;

	/*
		*  @brief Adds a component to the entity.
		*  @tparam T Type of the component, must be derived from Component.
		*  @param component Shared pointer to the component to add.
	*/
  template<typename T> 
	void
	addComponent(EngineUtilities::TSharedPointer<T> component) {
		static_assert(std::is_base_of<Component, T>::value, 
									"T must be derived from Component");
		components.push_back(component.template dynamic_pointer_cast<Component>());
  }

	/*
		*  @brief Retrieves a component of the specified type from the entity.
		*  @tparam T Type of the component to retrieve.
		*  @return Shared pointer to the component if found, otherwise an empty pointer.
	*/
	template<typename T> 
	EngineUtilities::TSharedPointer<T>
	getComponent() {
		for (auto& component : components) {
			EngineUtilities::TSharedPointer<T> 
			specificComponent = component.template dynamic_pointer_cast<T>();

			if (specificComponent) {
				return specificComponent;
			}
		}
		return EngineUtilities::TSharedPointer<T>();
	}

protected:
	/*
		*  @brief Indicates whether the entity is active.
	*/
	bool isActive = true;
	/*
		*  @brief Unique identifier for the entity.
	*/
	uint32_t id = 0;
	/*
		*  @brief List of components attached to the entity.
	*/
  std::vector<EngineUtilities::TSharedPointer<Component>> components;
};
