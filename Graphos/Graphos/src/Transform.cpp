#include "../include/ECS/Transform.h"

void
Transform::start() {
	
}

void
Transform::update(float deltaTime) {

}

void
Transform::render(const EngineUtilities::TSharedPointer<Window>& window) {
		
}

void
Transform::destroy() {
	
}

/*void
seek(const CVector2& targetPosition, float speed, float deltaTime, float range) {
	CVector2 direction = targetPosition - position;
	// Cambiar a mi raiz cuadrada
	float length = std::sqrt(direction.m_x * direction.m_x + direction.m_y * direction.m_y);

	if (length > range) {
		direction /= length; // Normalizar el vector de dirección
		position += direction * speed * deltaTime; // Mover la posición en la dirección normalizada
	}
}*/