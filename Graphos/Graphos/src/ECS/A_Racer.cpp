#include "ECS/A_Racer.h"
#include "ECS/Transform.h"
#include <algorithm>
#include <random>

A_Racer::A_Racer(const std::string& name, int initialPos)
  : Actor(name), m_initialPosIndex(initialPos), 
	  m_currentWaypointIndex(initialPos), m_speed(100.f) {}

void
A_Racer::update(float deltaTime) {
	Actor::update(deltaTime);

	if (!m_waypoints.empty()) {
		seekToWaypoint(deltaTime);
	}
}

void
A_Racer::setSpeed(float speed) {
	m_speed = speed;
}

void
A_Racer::setWayPoints(const std::vector<sf::Vector2f>& waypoints) {
	m_waypoints = waypoints;
	resetPos();
}

void
A_Racer::resetPos() {
  if(!m_waypoints.empty()) {
    m_currentWaypointIndex = m_initialPosIndex;
    getComponent<Transform>()->setPosition(m_waypoints[m_currentWaypointIndex]);
	}
}

/*
void
A_Racer::seekToWaypoint(float deltaTime) {
	auto transform = getComponent<Transform>();
	if (!transform) return;

	sf::Vector2f pos = transform->getPosition();
  sf::Vector2f targetPos = m_waypoints[m_currentWaypointIndex];
	sf::Vector2f direction = targetPos - pos;


	// Si llegó al waypoint, avanza al siguiente
	float dist = std::sqrt((pos.x - targetPos.x) * (pos.x - targetPos.x) +
												 (pos.y - targetPos.y) * (pos.y - targetPos.y));

	if (dist <= 10.0f) {
		m_currentWaypointIndex++;
		if(m_currentWaypointIndex >= static_cast<int>(m_waypoints.size())) {
			m_currentWaypointIndex = 0; // Reiniciar al primer waypoint si se supera el tamaño
		}

		targetPos = m_waypoints[m_currentWaypointIndex];
		direction = targetPos - pos;
	}

	// Normalizar la dirección
	float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	if(length > 0.0f) {
		direction.x /= length;
		direction.y /= length;
	}

	sf::Vector2f velocity = direction * m_speed * deltaTime;
	transform->setPosition(pos + velocity);
}


void A_Racer::seekToWaypoint(float deltaTime) {
	auto transform = getComponent<Transform>();
	if (!transform) return;

	sf::Vector2f pos = transform->getPosition();
	sf::Vector2f targetPos = m_waypoints[m_currentWaypointIndex];
	sf::Vector2f direction = targetPos - pos;

	float dist = std::sqrt(direction.x * direction.x + direction.y * direction.y);

	if (dist <= 10.0f) {
		m_currentWaypointIndex++;
		if (m_currentWaypointIndex >= static_cast<int>(m_waypoints.size())) {
			m_currentWaypointIndex = 0;
		}
		targetPos = m_waypoints[m_currentWaypointIndex];
		direction = targetPos - pos;
	}

	// Look Ahead: por ejemplo, 50 píxeles
	float lookAheadDistance = 75.0f;
	transform->seek(targetPos, m_speed, deltaTime, 10.0f, lookAheadDistance);
}
*/

/*
void 
A_Racer::seekToWaypoint(float deltaTime) {
	auto transform = getComponent<Transform>();
	if (!transform) return;

	// Waypoints
	int prevIdx = (m_currentWaypointIndex == 0) ? m_waypoints.size() - 1 : m_currentWaypointIndex - 1;
	int nextIdx = (m_currentWaypointIndex + 1) % m_waypoints.size();

	sf::Vector2f prev = m_waypoints[prevIdx];
	sf::Vector2f curr = m_waypoints[m_currentWaypointIndex];
	sf::Vector2f next = m_waypoints[nextIdx];

	// Curvatura
	float curvature = calculateCurvature(prev, curr, next);

	// Control de velocidad: menor velocidad en curvas cerradas
	float minSpeed = 80.0f;
	float maxSpeed = 250.0f;
	float curveFactor = 1.0f + curvature * 2.0f; // Ajusta el multiplicador según el mapa
	float targetSpeed = maxSpeed / curveFactor;
	targetSpeed = std::clamp(targetSpeed, minSpeed, maxSpeed);

	// "Follow Path": Interpolación para suavizar el giro
	sf::Vector2f pos = transform->getPosition();
	float t = 0.15f; // Qué tan lejos mira hacia el siguiente waypoint (ajusta para suavidad)
	sf::Vector2f lookAhead = curr + (next - curr) * t;

	// Seek al punto lookAhead
	sf::Vector2f direction = lookAhead - pos;
	float dist = std::sqrt(direction.x * direction.x + direction.y * direction.y);

	if (dist <= 10.0f) {
		m_currentWaypointIndex = nextIdx;
	}

	float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
	if (length > 0.0f) {
		direction /= length;
	}

	sf::Vector2f velocity = direction * targetSpeed * deltaTime;
	transform->setPosition(pos + velocity);
}

float 
A_Racer::calculateCurvature(const sf::Vector2f& prev, const sf::Vector2f& curr, const sf::Vector2f& next) {
	// Vectores entre puntos
	sf::Vector2f v1 = curr - prev;
	sf::Vector2f v2 = next - curr;

	// Normalizar
	float len1 = std::sqrt(v1.x * v1.x + v1.y * v1.y);
	float len2 = std::sqrt(v2.x * v2.x + v2.y * v2.y);
	if (len1 == 0 || len2 == 0) return 0.0f;
	v1 /= len1;
	v2 /= len2;

	// Ángulo entre vectores
	float dot = v1.x * v2.x + v1.y * v2.y;
	dot = std::clamp(dot, -1.0f, 1.0f);
	float angle = std::acos(dot); // En radianes

	// Curvatura proporcional al ángulo
	return angle;
}
*/

/* -- - En tu clase A_Racer-- -
// Añade estos miembros si no los tienes:
sf::Vector2f m_velocity{ 200.f, 200.f }; // Velocidad actual
float m_maxAcceleration = 400.f;   // Ajusta según tu juego

float A_Racer::calculateCurvature(const sf::Vector2f& prev, const sf::Vector2f& curr, const sf::Vector2f& next) {
	sf::Vector2f v1 = curr - prev;
	sf::Vector2f v2 = next - curr;
	float len1 = std::sqrt(v1.x * v1.x + v1.y * v1.y);
	float len2 = std::sqrt(v2.x * v2.x + v2.y * v2.y);
	if (len1 == 0 || len2 == 0) return 0.0f;
	v1 /= len1;
	v2 /= len2;
	float dot = v1.x * v2.x + v1.y * v2.y;
	dot = std::clamp(dot, -1.0f, 1.0f);
	float angle = std::acos(dot);
	return angle;
}

void A_Racer::seekToWaypoint(float deltaTime) {
	auto transform = getComponent<Transform>();
	if (!transform) { std::cout << "No Transform!\n"; return; }

	if (!transform || m_waypoints.size() < 2) return;

	int nextIdx = (m_currentWaypointIndex + 1) % m_waypoints.size();
	sf::Vector2f curr = m_waypoints[m_currentWaypointIndex];
	sf::Vector2f next = m_waypoints[nextIdx];

	// Curvatura y control de velocidad
	int prevIdx = (m_currentWaypointIndex == 0) ? m_waypoints.size() - 1 : m_currentWaypointIndex - 1;
	float curvature = calculateCurvature(m_waypoints[prevIdx], curr, next);
	float minSpeed = 80.f, maxSpeed = 250.f;
	float curveFactor = 1.0f + curvature * 2.0f;
	float targetSpeed = maxSpeed / curveFactor;
	targetSpeed = std::clamp(targetSpeed, minSpeed, maxSpeed);

	// Look-ahead dependiente de velocidad/tiempo
	float lookAheadTime = 0.7f; // segundos, ajusta según tu juego
	sf::Vector2f predictedPos = transform->getPosition() + m_velocity * lookAheadTime;

	// Proyección al segmento curr->next
	sf::Vector2f seg = next - curr;
	float segLen = std::sqrt(seg.x * seg.x + seg.y * seg.y);
	if (segLen == 0.f) return;
	sf::Vector2f segDir = seg / segLen;
	sf::Vector2f toPred = predictedPos - curr;
	float proj = toPred.x * segDir.x + toPred.y * segDir.y;
	proj = std::clamp(proj, 0.f, segLen);
	sf::Vector2f lookAheadTarget = curr + segDir * proj;

	// Avance por distancia sobre el segmento
	float distToNext = std::sqrt((transform->getPosition().x - next.x) * (transform->getPosition().x - next.x) +
		(transform->getPosition().y - next.y) * (transform->getPosition().y - next.y));
	if (proj >= segLen - 5.f || distToNext < 10.f) {
		m_currentWaypointIndex = nextIdx;
	}

	// Steering cinemático (aceleración)
	sf::Vector2f desiredVel = lookAheadTarget - transform->getPosition();
	float desiredLen = std::sqrt(desiredVel.x * desiredVel.x + desiredVel.y * desiredVel.y);
	if (desiredLen > 0.01f) {
		desiredVel /= desiredLen;
		desiredVel *= targetSpeed;
	}
	else {
		desiredVel = sf::Vector2f(0.f, 0.f);
	}

	sf::Vector2f acceleration = desiredVel - m_velocity;
	float accLen = std::sqrt(acceleration.x * acceleration.x + acceleration.y * acceleration.y);
	if (accLen > m_maxAcceleration) {
		acceleration = acceleration / accLen * m_maxAcceleration;
	}

	m_velocity += acceleration * deltaTime;
	float velLen = std::sqrt(m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y);
	if (velLen > targetSpeed) {
		m_velocity = m_velocity / velLen * targetSpeed;
	}

	transform->setPosition(transform->getPosition() + m_velocity * deltaTime);
}*/

// Simplifiquemos el seekToWaypoint: busca el siguiente waypoint y mueve al actor hacia él, y cada que esté apunto de llegar, da un valor al azar entre 50 - 100 para la velocidad

    // --- seekToWaypoint simplificado ---

    void A_Racer::seekToWaypoint(float deltaTime) {
        auto transform = getComponent<Transform>();
        if (!transform || m_waypoints.empty()) return;

        sf::Vector2f pos = transform->getPosition();
        sf::Vector2f targetPos = m_waypoints[m_currentWaypointIndex];
        sf::Vector2f direction = targetPos - pos;
        float dist = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        // Random engine (static to keep seed)
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_real_distribution<float> approachDist(m_minApproachSpeed, m_maxApproachSpeed);
        std::uniform_real_distribution<float> waypointDist(m_minWaypointSpeed, m_maxWaypointSpeed);

        // Si está cerca del waypoint, cambia al siguiente y ajusta velocidad
        if (dist <= m_arrivalThreshold) {
            m_currentWaypointIndex++;
            if (m_currentWaypointIndex >= static_cast<int>(m_waypoints.size())) {
                m_currentWaypointIndex = 0;
            }
            m_speed = waypointDist(gen);
            targetPos = m_waypoints[m_currentWaypointIndex];
            direction = targetPos - pos;
        } else if (dist <= m_arrivalThreshold * 5.0f) {
            // Cuando se acerca, cambia la velocidad para simular aceleración/desaceleración
            m_speed = approachDist(gen);
        }

        // Normalizar dirección
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length > 0.0f) {
            direction /= length;
        } else {
            direction = sf::Vector2f(0.f, 0.f);
        }

        sf::Vector2f velocity = direction * m_speed * deltaTime;
        transform->setPosition(pos + velocity);
    }
// para dar la sensación de que el actor va acelerando y desacelerando, y así no se vea tan robótico el movimiento.
// También, una vez que llegue al waypoint, se mueve al siguiente y aumenta la velocidad con un valor al azar entre 100 - 200, y si llega al último, vuelve al primero.
// Esos valores no los "hardcodees", sino que los pongas en una variable, para que puedas ajustar la jugabilidad fácilmente.