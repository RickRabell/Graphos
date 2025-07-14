#pragma once
#include "../Prerequisites.h"

class 
Window;

/**
* @enum ComponentType
* @brief Types of components available in the game.
*/
enum
ComponentType {
  /*
    *  @brief No component type.
  */
  NONE = 0,
  /*
    *  @brief Transform component type.
  */
  TRANSFORM = 1,
  /*
    *  @brief Sprite component type.
  */
  SPRITE = 2,
  /*
    *  @brief Renderer component type.
  */
  RENDERER = 3,
  /*
    *  @brief Physics component type.
  */
  PHYSICS = 4,
  /*
    *  @brief Audio source component type.
  */
  AUDIOSOURCE = 5,
  /*
    *  @brief Shape component type.
  */
  SHAPE = 6,
  /*
    *  @brief Texture component type.
  */
  TEXTURE = 7
};

/**
* @class Component
* @brief Abstract base class for all components in the ECS (Entity Component System).
* 
* The Component class defines the basic interface that all ECS components must implement,
* allowing updating and rendering of the component, as well as obtaining its type.
*/
class 
Component {
public:
  /*
    *  @brief Default constructor for Component.
  */
  Component() = default;

  /*
    *  @brief Constructor with component type.
    *  @param type The type of the component.
  */
  Component(const ComponentType type) : m_type(type) {}

  /*
    *  @brief Virtual destructor for Component.
  */
  virtual
  ~Component() = default;

  /*
    *  @brief Starts the component. Called once when the component is initialized.
  */
  virtual void
  start() = 0;

  /*
    *  @brief Updates the component.
    *  @param deltaTime Time elapsed since last update.
  */
  virtual void
  update(float deltaTime) = 0;

  /*
    *  @brief Renders the component.
    *  @param window Shared pointer to the Window where the component will be rendered.
  */
  virtual void
  render(const EngineUtilities::TSharedPointer<Window>& window) = 0;

  /*
    *  @brief Destroys the component and releases resources.
  */
  virtual void
  destroy() = 0;

  /*
    *  @brief Gets the type of the component.
    *  @return The ComponentType of this component.
  */
  ComponentType
  getType() const { return m_type; }

protected:
  /*
    *  @brief The type of the component.
  */
  ComponentType m_type = ComponentType::NONE; //Tipo de componente
};