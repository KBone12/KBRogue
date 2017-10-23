#include "entity.hpp"

#include "map.hpp"

using kb::rogue::Entity;
using kb::rogue::Map;

Entity::Entity(const std::shared_ptr<Map>& map, char mark, int x0, int y0, bool passable)
	: map(map), mark(mark),
	x(x0), y(y0), mapX0(map->getX0()), mapY0(map->getY0()),
	passable(passable)
{}
