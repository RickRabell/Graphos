#pragma once
#include "Prerequisites.h"
#include "SFML/System/Vector2.hpp"
//#include "../Utilities/CVector2.h"
#include "ECS/Component.h"
#include "../Window.h"
/*
	*  @brief Encapsulates an SFML RenderWindow for rendering and window management. It is a forward declaration to avoid circular dependencies.
*/
class 
Window;

/*
  *  @class Transform
  *  @brief Transform component for position, rotation, and scale in ECS.
  *
  *  The Transform class is a component used in the Entity Component System (ECS) architecture
  *  to manage the spatial properties of an entity, including its position, rotation, and scale.
  *  It provides getter and setter methods for these properties, allowing other systems and components
  *  to query and modify the entity's transform. The class inherits from Component and implements
  *  the required lifecycle methods: start, update, render, and destroy.
  *
  *  @note This component does not perform any rendering itself, but its data can be used by
  *  rendering systems to position and orient entities in the scene.
*/
class 
Transform : public Component {
public:
  /*
    *  @brief Default constructor for Transform.
  */
  //Transform() = default;

  /*
    *  @brief Constructor for Transform.
  */
  Transform() :
    m_position(0.0f, 0.0f),
    m_rotation(0.0f, 0.0f),
    m_scale(1.0f, 1.0f), 
    Component(ComponentType::TRANSFORM) {}
  
  /*
    *  @brief Virtual destructor for Transform.
  */
  virtual
  ~Transform() = default;

  //Component
  /*
    *  @brief Starts the Transform component.
  */
  void
  start() override;

  /*
    *  @brief Updates the Transform component.
    *  @param deltaTime Time elapsed since last update.
  */
  void
  update(float deltaTime) override;

  /*
    *  @brief Renders the Transform component.
    *  @param window Shared pointer to the Window for rendering.
  */
  void
  render(const EngineUtilities::TSharedPointer<Window>& window) override;
  
  /*
    *  @brief Destroys the Transform component and releases resources.
  */
  void
  destroy() override;

  // Getters
  /*
    *  @brief Gets the position of the Transform.
    *  @return The position as sf::Vector2f.
  */
  sf::Vector2f
  getPosition() const { return m_position; }

  /*
    *  @brief Gets the rotation of the Transform.
    *  @return The rotation as sf::Vector2f.
  */
  sf::Vector2f
  getRotation() const { return m_rotation; }
  
  /*
    *  @brief Gets the scale of the Transform.
    *  @return The scale as sf::Vector2f.
  */
  sf::Vector2f
  getScale() const { return m_scale; }

  // Setters
  /*
    *  @brief Sets the position of the Transform.
    *  @param position The new position as sf::Vector2f.
  */
  void
  setPosition(const sf::Vector2f& position) { m_position = position; }

  /*
    *  @brief Sets the rotation of the Transform.
    *  @param rotation The new rotation as sf::Vector2f.
  */
  void
  setRotation(const sf::Vector2f& rotation) { m_rotation = rotation; }

  /*
    *  @brief Sets the scale of the Transform.
    *  @param scale The new scale as sf::Vector2f.
  */
  void
  setScale(const sf::Vector2f& scale) { m_scale = scale; }

  void
  seek(const sf::Vector2f& targetPosition, float speed, float deltaTime, float range) {
    sf::Vector2f direction = targetPosition - m_position;
    // Cambiar a mi raiz cuadrada
    float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

    if (length > range) {
      direction /= length; // Normalizar el vector de dirección
      m_position += direction * speed * deltaTime; // Mover la posición en la dirección normalizada
    }
  }

  float*
  getPosData() {
		return &m_position.x; // Retorna un puntero al primer elemento del vector de posición
  }

	float*
  getRotData() {
    return &m_rotation.x; // Retorna un puntero al primer elemento del vector de rotación
	}

	float*
  getScaleData() {
		return &m_scale.x; // Retorna un puntero al primer elemento del vector de escala
  }

private:
  /*
    *  @brief Position of the Transform component.
  */
  sf::Vector2f m_position;
  /*
    *  @brief Rotation of the Transform component.
  */
  sf::Vector2f m_rotation;
  /*
    *  @brief Scale of the Transform component.
  */
  sf::Vector2f m_scale;
};