#include "collision.hpp"

#include "entity.hpp"
#include "map.hpp"
#include "player.hpp"

using kb::rogue::CollisionDetector;
using kb::rogue::CollisionType;
using kb::rogue::Map;

CollisionType CollisionDetector::collision(const int x, const int y, const std::shared_ptr<Map>& map)
{
	if (map->getPlayer()->getX() == x && map->getPlayer()->getY() == y)
		return CollisionType::PLAYER;
	if (map->getEntity(x, y))
		return (map->getEntity(x, y)->isPassable())
			? CollisionType::ENTITY_PASSABLE
			: CollisionType::ENTITY_NOT_PASSABLE;
	else if (map->getEnemy(x, y))
		return CollisionType::ENEMY;
	// Any collisionData has wall around the map
	switch (map->getCollisionData().at(y + 1).at(x + 1))
	{
		case Map::WALL:
			return CollisionType::WALL;
		case Map::FLOOR:
			return CollisionType::NONE;
		default:
			return CollisionType::UNKNOWN;
	}
}
