#include "collision.hpp"

#include "entity.hpp"
#include "map.hpp"

using kb::rogue::CollisionDetector;
using kb::rogue::Map;

bool CollisionDetector::collision(const int x, const int y, const std::shared_ptr<Map>& map)
{
	if (map->getEntity(x, y))
		return !map->getEntity(x, y)->isPassable();
	else if (map->getEnemy(x, y))
		return true;
	// Any collisionData has wall around the map
	switch (map->getCollisionData().at(y + 1).at(x + 1))
	{
		case Map::WALL:
			return true;
		case Map::FLOOR:
			return false;
		default:
			return false;
	}
}
