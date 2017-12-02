#include "mob.hpp"

#include "item.hpp"
#include "map.hpp"

using kb::rogue::Item;
using kb::rogue::Mob;

Mob::Mob(const std::shared_ptr<Map>& map, char mark, int x0, int y0, int hp)
	: map(map), items(), mark(mark),
	mapX0(map->getX0()), mapY0(map->getY0()), x(x0), y(y0), hp(hp)
{}
