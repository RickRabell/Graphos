  // Ordenar por (laps desc, currentWaypoint desc, distToNext asc, totalTime asc)
  std::sort(validActors.begin(), validActors.end(), [](const auto& a, const auto& b) {
    if (a->getLaps() != b->getLaps())
      return a->getLaps() > b->getLaps();
    if (a->m_currentWaypointIndex != b->m_currentWaypointIndex)
      return a->m_currentWaypointIndex > b->m_currentWaypointIndex;

    float aDist = 0.f, bDist = 0.f;
    // Métodos utilitarios para obtener distancia al siguiente waypoint
    auto aPlayer = dynamic_cast<const A_Player*>(a.get());
    auto bPlayer = dynamic_cast<const A_Player*>(b.get());
    
    // Safe distance calculations with waypoint size checks
    if (aPlayer) {
        aDist = aPlayer->getDistToNextWaypoint();
    } else if (!a->m_waypoints.empty()) {
        aDist = Distance(a->getComponent<Transform>()->getPosition(),
            a->m_waypoints[(a->m_currentWaypointIndex + 1) % a->m_waypoints.size()]);
    }
    
    if (bPlayer) {
        bDist = bPlayer->getDistToNextWaypoint();
    } else if (!b->m_waypoints.empty()) {
        bDist = Distance(b->getComponent<Transform>()->getPosition(),
            b->m_waypoints[(b->m_currentWaypointIndex + 1) % b->m_waypoints.size()]);
    }
    
    if (aDist != bDist)
      return aDist < bDist;

    // Desempate por tiempo total (si existe)
    float aTime = 0.f, bTime = 0.f;
    if (aPlayer) aTime = aPlayer->getTotalTime();
    if (bPlayer) bTime = bPlayer->getTotalTime();
    return aTime < bTime;
  });