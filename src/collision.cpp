#include "collision.hpp"

#include "map.hpp"

using kb::rogue::CollisionDetector;
using kb::rogue::Map;

bool CollisionDetector::collision(const int x, const int y, const std::shared_ptr<Map>& map)
{
	// Any collisionData has wall around the map
	return map->getCollisionData().at(y + 1).at(x + 1) != 0;
}
